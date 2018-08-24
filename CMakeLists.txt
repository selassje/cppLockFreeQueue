cmake_minimum_required (VERSION 3.5)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin) 

project (lfQueue)

add_executable(lfQueueTest src/tests/mainTests.cpp
                           src/tests/basic.cpp )