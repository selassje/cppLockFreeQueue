conan  install -s build_type=Debug -s compiler.toolset=v141 ../..
cmake  ../..
cmake --build . --config Debug
