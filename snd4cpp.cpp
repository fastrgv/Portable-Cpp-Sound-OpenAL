
//# -- Copyright (C) 2021  <fastrgv@gmail.com>
//# --
//# -- This program is free software: you can redistribute it and/or modify
//# -- it under the terms of the GNU General Public License as published by
//# -- the Free Software Foundation, either version 3 of the License, or
//# -- (at your option) any later version.
//# --
//# -- This program is distributed in the hope that it will be useful,
//# -- but WITHOUT ANY WARRANTY; without even the implied warranty of
//# -- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//# -- GNU General Public License for more details.
//# --
//# -- You may read the full text of the GNU General Public License
//# -- at <http://www.gnu.org/licenses/>.


// using c++ pthreads to access OpenAL


#include "snd4cpp.hpp"

#include <sleep.hpp> // my own "msleep"


#include <string>
using std::string;

#include <iostream>
#include <fstream>
using std::ifstream;
using std::cout;
using std::endl;

#include <cstring>

#include <al.h>
#include <alc.h>

#include <pthread.h>

#include <atomic>

#include <cassert>








// transient sounds here:
static long nsnd(0);
static const long mxsnd(26);

static string buf[mxsnd];

// pthread flags for start/stop music:
std::atomic<bool> tstart[mxsnd], tstop[mxsnd], tquit[mxsnd];

///////// begin insert /////////////////////////////////////////////



///////// begin utils /////////////////////////////////////////////


bool isBigEndian()
{
    int a = 1;
    return !((char*)&a)[0];
}

int convertToInt(char* buffer, int len)
{
    int a = 0;
    if (!isBigEndian())
        for (int i = 0; i<len; i++)
            ((char*)&a)[i] = buffer[i];
    else
        for (int i = 0; i<len; i++)
            ((char*)&a)[3 - i] = buffer[i];
    return a;
}

char* loadWAV(
	const char* fn, 
	int& chan, 
	int& samplerate, 
	int& bps, 
	int& size)
{
    char buffer[4];
    std::ifstream in(fn, std::ios::binary);
    in.read(buffer, 4);		// 0..3
    if (strncmp(buffer, "RIFF", 4) != 0)
    {
        std::cout << "this is not a valid WAVE file" << std::endl;
        return NULL;
    }
    in.read(buffer, 4);			// 4..7
    in.read(buffer, 4);      //WAVE 8..11
    in.read(buffer, 4);      //fmt  12..15
    in.read(buffer, 4);      //16   16..19
    in.read(buffer, 2);      //1    20..21
    in.read(buffer, 2);			// 22..23
    chan = convertToInt(buffer, 2);

    in.read(buffer, 4);			// 24..27
    samplerate = convertToInt(buffer, 4);

    in.read(buffer, 4);			// 28..31
    in.read(buffer, 2);
    in.read(buffer, 2);
    bps = convertToInt(buffer, 2);
    in.read(buffer, 4);      //data
    in.read(buffer, 4);
    size = convertToInt(buffer, 4);
    char* data = new char[size];
    in.read(data, size);

//cout<<"SampleRate="<<samplerate<<endl; //debug (seems Ok)

    return data;
} // end original loadWav





///////// end utils /////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////

	// OpenAL state variables for up to 26 tasks:

	const long mx(mxsnd);

	unsigned int sourceid[mx];
	unsigned int bufferid[mx]; //, format[mx];

	char* data[mx];

	// only 1 each of these:
	ALCcontext* context;	
	ALCdevice* device;



///////////////////////////////////////////////////////////////////////

// all OpenAL initializations (single-threaded):
void taskprep(int j, const char * name)
{
	unsigned int format;
	int sampleRate, bps, size, channel;

	data[j] = loadWAV(name, channel, sampleRate, bps, size);



	alGenBuffers(1, &bufferid[j]);

	if (channel == 1)
		if (bps == 8) format = AL_FORMAT_MONO8;
		else          format = AL_FORMAT_MONO16;
	else 
		if (bps == 8) format = AL_FORMAT_STEREO8;
		else          format = AL_FORMAT_STEREO16;

	alBufferData(bufferid[j], format, data[j], size, sampleRate);
	alGenSources(1, &sourceid[j]);
	alSourcei(sourceid[j], AL_BUFFER, bufferid[j]);


} // end taskprep

///////////////////////////////////////////////////////////////////////





// multi-threaded:
void * playonce(void * k) // j in 0..25
{
	long j = (long) k;
	ALint state;
	const unsigned int sid( sourceid[j] );
	while(true) {
		if( tstart[j].load() ) {
			tstart[j].store(false);
			alSourcePlay(sid); // begin play
			do {
				alGetSourcei(sid, AL_SOURCE_STATE, &state);
				if( tstop[j].load() ) break;
			} while( AL_PLAYING == state );
			alSourceStop(sid);
		} // end if tstart
		if( tquit[j].load() ) break;
		msleep(100); // 0.1 sec
	} //end while true

	pthread_exit(NULL);

} // end playonce


///////////////////////////////////////////////////////////////////////



// multi-threaded:
void * taskloop(void * k) // thread j, j in 0..25
{
	long j = (long) k;

	ALint state;
	const unsigned int sid( sourceid[j] );
	while(true) {
		if( tstart[j].load() ) {
			tstart[j].store(false);
			alSourcePlay(sid); // begin play
			while( !tstop[j].load() ) { //=====================
				alGetSourcei(sid, AL_SOURCE_STATE, &state);
				if (state==AL_STOPPED) {
					alSourcePlay(sid); //restart
				}
			} // end while =====================================
			alSourceStop(sid);
		} // end if tstart
		if( tquit[j].load() )	break;
		msleep(100); // 0.1 sec
	} // end while true
	// ready to join()

	pthread_exit(NULL);

} // end taskloop
///////////////////////////////////////////////////////////////////////


void taskend(long j)
{
	alDeleteSources(1, &sourceid[j]);
	alDeleteBuffers(1, &bufferid[j]);
	delete[] data[j];

} // end taskend




///////////////////////////////////////////////////////////////////////


pthread_t tsk[mxsnd];
pthread_attr_t attr;


bool isloop[mxsnd], running[mxsnd];



///////////////////////////////////////////////////////////////////////





void quitAll(void) {

	for(int i=0; i<nsnd; i++)
	{
		tquit[i].store(true);
	}

}


void joinAll(void) {

	for(int i=0; i<nsnd; i++) {

		void * status = 0;

		int rc=pthread_join(tsk[i], &status);

		if (rc) {
			printf("ERROR; return code from pthread_join() is %d\n", rc);
			exit(-1);
		}

		taskend(i);

		printf(
				"Main: completed join with thread %ld having a status of %ld\n"
				,(long)i,(long)status);
	}
}




void stopLoops(void) {
	for(int i=0; i<nsnd; i++) 
		stopLoop(i);
}


void termSnds(void)
{
	stopLoops();
	quitAll(); // quit

pthread_attr_destroy(&attr);

	joinAll(); // join

	cout<<"termSnds all joined"<<endl;

	alcDestroyContext(context);
	alcCloseDevice(device);

	cout<<"termSnds completed"<<endl;
}



void initSnds(void) 
{
	for(int i=0; i<mxsnd; i++) {
		running[i]=false;
		isloop[i]=false;
		tstart[i].store(false);
		tstop[i].store(false);
		tquit[i].store(false);
	}


////////////////////////////////////////////////////////////////
	// need single device, single context:

	device = alcOpenDevice(NULL);
	if (device == NULL)
	{
		std::cout << "cannot open sound card" << std::endl;
	}

	context = alcCreateContext(device, NULL);
	if (context == NULL)
	{
		std::cout << "cannot open context" << std::endl;
	}
	assert(device!=NULL);
	assert(context!=NULL);

	alcMakeContextCurrent(context);

////////////////////////////////////////////////////////////////

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


}


int initSnd(const char * pc)
{
	int rc;
	assert( nsnd<mxsnd-1 );
	buf[nsnd]=pc;
	isloop[nsnd]=false;
	taskprep(nsnd, pc);
	//rc=pthread_create( &tsk[nsnd], NULL, playonce, (void*)nsnd );
	rc=pthread_create( &tsk[nsnd], &attr, playonce, (void*)nsnd );
	if(rc) assert(false);
	nsnd++;
	return nsnd-1;
}

void playSnd( int nbuf ) {  // plays indexed sound

	//if( ( nbuf<nsnd ) && ( nbuf>=0 ) )
	if( ( nbuf<nsnd ) && ( nbuf>=0 ) && ( !isloop[nbuf] ) )
	{
		tstart[nbuf].store(true);
	}

} // end playSnd


int initLoop(const char * pc )
{
	int rc;
	assert( nsnd<mxsnd-1 );
	buf[nsnd]=pc;
	isloop[nsnd]=true;
	taskprep(nsnd, pc);
	//rc=pthread_create( &tsk[nsnd], NULL, taskloop, (void*)nsnd );
	rc=pthread_create( &tsk[nsnd], &attr, taskloop, (void*)nsnd );
	if(rc) assert(false);
	nsnd++;
	return nsnd-1;
}

void playLoop( int nbuf ) {

	if( ( nbuf<nsnd ) && ( nbuf>=0 ) && ( isloop[nbuf] ) && (false==running[nbuf]) )
	{
		//send start signal
		tstop[nbuf].store(false);
		tstart[nbuf].store(true);
		running[nbuf]=true;
	}

}

void stopLoop(int nbuf) {

	if( ( nbuf<nsnd ) && (isloop[nbuf]) && ( nbuf>=0 ) && (true==running[nbuf]) )
	{
		//send stop signal
		tstart[nbuf].store(false);
		tstop[nbuf].store(true);
		running[nbuf]=false;

	}
}



