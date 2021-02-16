
Here is the main release with all source code and resources:

https://github.com/fastrgv/Portable-Cpp-Sound-OpenAL/releases/download/v1.0.2/cppOal_17feb21.7z


# Portable C++ Sound using OpenAL

## Sound utility for Windows, OSX, and Linux

**ver 1.0.2 -- 17feb2021**
* New stand-alone release.

**ver 1.0.1 -- 20nov2020**
* Added important guard statements for robustness.
* Reordered thread termination steps.
* All theads are now guaranteed joinable at creation.

**ver 1.0.0 -- 15nov2020**
* Initial release.



## Description

This is a cross-platform sound-playing package for C++ apps that can asynchronously start and stop music loops, as well as initiate transient sounds.

It plays WAV files, via OpenAL, on Windows, OSX, and linux platforms.

It is suitable for any Cpp application that needs music, sound loops or transient sound effects; eg. games.

--------------------------------------------------------
## Usage:

See the simple interface description in file snd4cpp.hpp.

Generally, when you initialize a sound or soundloop, you specify its file name and retrieve an integer "key" that is used to play it sometime later.

Note: an error occurs if there is something fishy about the WAV file. I always get good results with WAV files output from, or processed through "sox".

========================================================
## What is so great about this package?

This package is a non-platform-specific C++ code that uses Pthreads and compiles on Windows, OSX and Linux. It is used in my games RufasGate & RufasSliders (on SourceForge and GitHub).


========================================================

## Examples:

See ./examples/one.adb
See ./examples/two.adb

The examples come with 3 compilation scripts: lcmp.sh, ocmp.sh, wcmp.bat
These scripts assume your c++ compiler is visible.

Note that the Windows executables need to be colocated with

	openal32.dll
		&
	pthreadGC2.dll

in order to run. (included).

--------------------------
## License:


This app is covered by the GNU GPL v3 as indicated in the sources:


Copyright (C) 2021  <fastrgv@gmail.com>

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


