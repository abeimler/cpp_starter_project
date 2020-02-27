#!/bin/bash

find benchmark/ -iname *.h -o -iname *.cpp | xargs clang-format -i -style=file
find fuzz_test/ -iname *.h -o -iname *.cpp | xargs clang-format -i -style=file
find src/ -iname *.h -o -iname *.cpp | xargs clang-format -i -style=file
find test/ -iname *.h -o -iname *.cpp | xargs clang-format -i -style=file