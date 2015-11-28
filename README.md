[![Build Status](https://travis-ci.org/bysreg/anjing.svg?branch=master)](https://travis-ci.org/bysreg/anjing)
[![Build status](https://ci.appveyor.com/api/projects/status/qw871xxhxlhd0j3a?svg=true)](https://ci.appveyor.com/project/bysreg/anjing)

##Support:##
- OS : Windows (msvc), Linux (gcc & clang), OSX (gcc & clang)

##Dependency :##
- OpenGL 3.0 
- GLEW 1.12.0
- SDL 2.0.3
- Doxygen 1.8.10 (for docs)
- CMake 3.1.0
- Google Test 1.7.0 (included in source)
- C++ 11 supported compiler

##For windows :##
add folder /windows/bin to your path

##How to build:##
- go to folder build, and run this from terminal in linux/osx or cmd in windows: "cmake ..".
- the previous step will make all necessary build files according to the platform.
- if you're on linux/osx, do "make install", and then the program will be build in the project's root folder. 
- if you're on windows, 
  - open the visual studio .sln file, 
  - set the myapp project as the startup project, and build that project. 

##Program's argument :##
- -y : automatically close the command line program after the main window closes


##Documentation :##
http://bysreg.github.io/anjing/index.html

##Updating Doxygen Documentation :##
- go to /docs, and then run "doxygen" in terminal or cmd
- to update the documentation on the anjing's github page : 
  - switch to gh-pages branch
  - merge with the origin's master branch
  - go to /docs, and then run "doxygen" in terminal or cmd
  - note that, HTML_OUTPUT in Doxyfile is set to the project root folder instead of /docs

##Building with GTest switched on:##
- if on linux, 
  - you need to build gtest first, and put the libgtest.a nd libgtest-main.a to /usr/lib
- use "cmake -Dbuild_test=ON .."
- if on windows, 
  - instead of myapp project as the startup project, set the "appTestExecutable" as the startup project, and build that project
  - use ctrl+F5, so that the program won't immediately quit so that you can see the test's results. 
- if on linux, 
  - run "make" to build all executables, including the tests
  - run "make test" to run all the tests
  
  
##C++ 11 features needed :##
- Deleted functions, as defined in http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2346.htm
- Null pointer, as defined in http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2431.pdf
- Strongly typed enums, as defined in http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2347.pdf  
  
  
  
