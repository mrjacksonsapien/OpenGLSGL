# OpenGLSGL

## Description
This project is a re-imagined version of the SGL engine made in JS for web browsers that didn't leverage hardware acceleration (GPU) APIs and did all the 3D through software-rendering. The same classes are used but instead we use OpenGL and C++ for a more "realistic" type of engine. 

**Warning: This project is for learning purpose of the OpenGL API, CMake tool and C++ language so it's not a fully optimized engine ready for use.**

## Git instructions (IMPORTANT)

Do all git cloning/fetching/pulling with this option to also get up-to-date submodules since other third-party repositories are referenced in this project.

`--recurse-submodules`

## Build and run project

PS: Make sure you have CMake and Makefile installed

### 1. Set up CMake and build cmake files
/> `mkdir build`

/> `cd build`

/build> `cmake -S .. -B .`

/build> `cmake --build .`

### 2. Build project

/build> `make`

/build> `./OpenGLSGL`