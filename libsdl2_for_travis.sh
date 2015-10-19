#!/bin/bash
# download libsdl2 2.0.3 source code, and install it

cd ~
mkdir sdl2
export SDL2="`pwd`/sdl2"
wget https://www.libsdl.org/release/SDL2-2.0.3.tar.gz
tar xzf SDL2-2.0.3.tar.gz
cd SDL2-2.0.3
./configure --prefix=$SDL2
make
make install

