conan install -s compiler.libcxx=libstdc++11 "../.." --build missing
cmake "../.."
cmake --build .
