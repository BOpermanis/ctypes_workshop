# About

This is an example of building a (simple) C++ class and interfacing it to Python via ctypes.

## Workplace setup
# linux
`sudo apt install cmake make gcc g++`

# windows

  - Download latest cmake for windows https://cmake.org/download/
  - Download and install g++ as described here https://www3.cs.stonybrook.edu/~alee/g++/g++.html
  - Install visual studio 2019 https://visualstudio.microsoft.com/downloads/  

## Building the shared library

# On linux
To build use:
`cmake .` to build the `makefile`, and then build with `make`.

# On windows
- configure and generate build files with Cmake (Visual studio as generator)
- open interface_class.vcxproj with visual studio (creating windows account may be needed),
- Tools -> Command Line -> Developer Command Prompt 
 - `msbuild  interface_class.vcxproj`

## Workshop

Uncompleted code is in `workshop` branch

## Recources

* [Auctoris](https://github.com/Auctoris/ctypes_demo)
* [justinhj](https://github.com/justinhj/astar-algorithm-cpp)

