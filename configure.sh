#!/bin/bash

##
# generate sourcefile list with cogapp
# you don't need to generate this files every time, only if you add, delete or move files
# pip install cogapp
##
## TODO: add CMakeLists.txt files with cog source here
python3 -m cogapp -r ./benchmark/benchmarks/CMakeLists.txt
python3 -m cogapp -r ./fuzz_test/CMakeLists.txt
python3 -m cogapp -r ./src/app/engine/CMakeLists.txt
python3 -m cogapp -r ./src/app/desktop/CMakeLists.txt
python3 -m cogapp -r ./src/app/raspberrypi/CMakeLists.txt
python3 -m cogapp -r ./src/core/CMakeLists.txt
python3 -m cogapp -r ./src/persistence/bitsery/CMakeLists.txt
python3 -m cogapp -r ./src/persistence/json/CMakeLists.txt
python3 -m cogapp -r ./test/tests/CMakeLists.txt
python3 -m cogapp -r ./test/constexpr_tests/CMakeLists.txt

# you cmake as usual
cmake . -Bbuild -DBUILD_SHARED_LIBS:BOOL="0" -DBUILD_TESTING:BOOL="0" -DBUILD_TESTS:BOOL="0" -DSTATIC:BOOL="1" -DSHARED:BOOL="0" ..
