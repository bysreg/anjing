pushd "../build_clang/"
cmake .. -Dbuild_test=ON -TLLVM-vs2014 -G"Visual Studio 14 2015"
popd