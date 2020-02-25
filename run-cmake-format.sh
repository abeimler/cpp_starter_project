#!/bin/bash

find benchmark/ -iname CMakeLists.txt | xargs cmake-format -i 
find fuzz_test/ -iname CMakeLists.txt | xargs cmake-format -i 
find src/ -iname CMakeLists.txt | xargs cmake-format -i 
find test/ -iname CMakeLists.txt | xargs cmake-format -i 