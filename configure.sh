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
python3 -m cogapp -r ./src/app/fltk/CMakeLists.txt
python3 -m cogapp -r ./src/app/gtkmm/CMakeLists.txt
python3 -m cogapp -r ./src/app/imgui/CMakeLists.txt
python3 -m cogapp -r ./src/app/intro/CMakeLists.txt
python3 -m cogapp -r ./src/app/nana/CMakeLists.txt
python3 -m cogapp -r ./src/app/qt/CMakeLists.txt
python3 -m cogapp -r ./src/app/sdl/CMakeLists.txt
python3 -m cogapp -r ./src/core/CMakeLists.txt
python3 -m cogapp -r ./test/tests/CMakeLists.txt
python3 -m cogapp -r ./test/constexpr_tests/CMakeLists.txt
python3 -m cogapp -r ./test/integrartion_tests/CMakeLists.txt

# you cmake as usual
cmake . -Bbuild ..
