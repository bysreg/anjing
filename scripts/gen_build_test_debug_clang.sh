#!/bin/bash

cd ../build/
CC=clang CXX=clang++ cmake -Dbuild_test=ON -DCMAKE_BUILD_TYPE=Debug ..
