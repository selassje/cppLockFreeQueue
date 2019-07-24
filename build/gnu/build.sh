conan install -s arch=x86_64 -s arch_build=x86_64 -s compiler=gcc -s compiler.libcxx=libstdc++ -s compiler.version=7  --build=missing ../..
cmake "../.."
cmake --build .
