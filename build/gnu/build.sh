conan install -s arch=x86_64 --build missing
cmake "../.."
cmake --build .
