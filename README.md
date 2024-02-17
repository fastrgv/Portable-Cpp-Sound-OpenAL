
![screenshot](https://github.com/fastrgv/Portable-Cpp-Sound-OpenAL/blob/main/cppSound.jpeg)


Here is the main release with all source code, examples and resources:

https://github.com/fastrgv/Portable-Cpp-Sound-OpenAL/releases/download/v1.0.6/coal6oct23.7z

Type "7z x filename" to extract the archive.

* On OSX, Keka works well for 7Z files. The command-line for Keka is:
	* /Applications/Keka.app/Contents/MacOS/Keka --cli 7z x (filename.7z)



### Note: Please ignore the "Source code" zip & tar.gz files. (They are auto-generated by GitHub). Click on the large 7z file under releases to download all source & binaries (Windows,Mac & Linux). Then, type "7z x filename" to extract the archive. 








another link:
https://sourceforge.net/projects/portable-cpp-sound-openal/


# Portable C++ Sound -- using pthreads & OpenAL
## Sound utility for Windows, OSX, & Linux

**ver 1.0.7 -- 18feb2024**

* Added volume control.


**ver 1.0.6 -- 06oct2023**

* Updated support of Mac/OSX.


**ver 1.0.5 -- 09nov2022**

* Updated Windows script [& DLLs] to W64.


**ver 1.0.4 -- 16sep2022**

* Updated to use GNU g++ for OSX, linux, W32.


**ver 1.0.3 -- 27apr2022**

* Updated DLLs for 32-bit Windows examples.
* Added scripts & DLLs for 64-bit Windows example.
* Improved coding.

**ver 1.0.2 -- 17feb2021**

* New stand-alone release.

**ver 1.0.1 -- 20nov2020**

* Added important guard statements for robustness.
* Reordered thread termination steps.
* All theads are now guaranteed joinable at creation.

**ver 1.0.0 -- 15nov2020**

* Initial release.



## Brief Description
Cross platform sound-playing utility for C++ apps with its own binding to OpenAL.



## Full Description


This is a sound-playing utility for C++ that can play WAV files on Windows, OSX, and Linux, using pthreads and OpenAL libraries.

It provides sound-playing capabilities for C++ apps to:

* asynchronously start and stop music/sound loops, 
* initiate transient sounds,
* allow unlimited sound concurrency.


It plays WAV files, via OpenAL, and runs on Windows, OSX, and linux platforms. Nice examples for each O.S. are included.

It is suitable for any C++ application that needs music, sound loops or transient sound effects; eg. games.

There are no software depencies; this utility is self-contained.

* I am currently using it for sound in my OpenGL slider-puzzles app RufasSlider (written in C++): https://sourceforge.net/projects/rufasslider/

--------------------------------------------------------
## Usage:

The proper command to extract the archive and maintain the directory structure is "7z x filename".
On OSX you can use Keka.

See the simple interface description in file snd4cpp.hpp.

Generally, when you initialize a sound or soundloop, you specify its file name and retrieve an integer "key" that is used to play it sometime later.

Note: an error occurs if there is something fishy about the WAV file. I always get good results with WAV files output from, or processed through "sox".

========================================================
## What is so great about this package?

This package is a non-platform-specific C++ code that uses Pthreads and compiles on Windows, OSX and Linux. It is used in my game RufasSliders (on SourceForge and GitHub).

Open source developers are welcome to help improve or extend this app.
Developer or not, send comments, suggestions or questions to:
fastrgv@gmail.com


========================================================

## Example:

See ./examples/two.adb

The example comes with 3 compilation scripts: lcmp.sh, ocmp.sh, wcmp.bat
These scripts assume your c++ compiler is visible.

Note that the Windows executables need to be colocated with the DLLs provided in order to run.

## SoundFiles
mKickCC0 & choirCC3 sounds are from freesound.org, and are covered by the Creative Commons CC0/CC3 Licenses. Attribution of choirCC3.wav is "dobroide".

## Getting a free Ada (& g++) compiler
To find a recent Ada compiler;  eg. GNU-Ada...try this source:
	https://github.com/alire-project/GNAT-FSF-builds/releases


--------------------------
## License:


This app is covered by the GNU GPL v3 as indicated in the sources:


Copyright (C) 2023  <fastrgv@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You may read the full text of the GNU General Public License
at <http://www.gnu.org/licenses/>.



