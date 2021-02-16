
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


#ifndef SND4CPP_HPP
#define SND4CPP_HPP


void termSnds(void);

int initLoop(const char * pc);

void initSnds(void);

int initSnd(const char * pc);

void stopLoop(int nbuf);

void stopLoops(void);

void playLoop( int nbuf );

void playSnd( int nbuf );

#endif

