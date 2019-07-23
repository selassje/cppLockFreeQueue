conan install -s arch=x86_64 -s compiler=gcc -s compiler.libcxx=libstdc++11 -s compiler.version=7 "../.." --build missing
cmake -G "$CMAKE_GENERATOR" "../.."
cmake --build .
