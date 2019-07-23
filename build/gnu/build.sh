conan install -s arch=x86_64 -s arch_build=x86_64 ../.. --build missing
cmake "../.."
cmake --build .
