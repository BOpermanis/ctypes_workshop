# About

This is an example of building a (simple) C++ class and interfacing it to Python via ctypes.

## Workplace setup
# linux
`sudo apt install cmake make gcc g++`

# windows

  - Download and install cygwin https://cygwin.com/install.html
  - Download latest cmake for windows https://cmake.org/download/
  - Download and install g++ as described here https://www3.cs.stonybrook.edu/~alee/g++/g++.html

  
## Building the shared library

To build use:
`cmake .` (or `cmake.exe .\CMakeLists.txt ` on windows) to build the `makefile`, and then build with `make` (or `make.exe ` on windows).

## Workshop

Uncompleted code is in `workshop` branch

## Recources

* [Auctoris](https://github.com/Auctoris/ctypes_demo)
* [justinhj](https://github.com/justinhj/astar-algorithm-cpp)
