#!/bin/bash

cd ../build/
cmake -Dbuild_test=ON -DCMAKE_BUILD_TYPE=Release ..
