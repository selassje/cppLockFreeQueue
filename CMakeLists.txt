cmake_minimum_required (VERSION 3.5)

project (lfQueue)

message("CMake version ${CMAKE_VERSION}")
message("CMake generator ${CMAKE_GENERATOR}")
message("Compiler ${CMAKE_CXX_COMPILER_ID}")
message("Compiler Version ${CMAKE_CXX_COMPILER_VERSION}")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin") 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}) 

list(APPEND MSVC_ADD_CXX_FLAGS "/w14242" "/w14254" "/w14263" "/w14265" "/w14287" "/we4289" "/w14296" "/w14311")
list(APPEND MSVC_ADD_CXX_FLAGS "/w14545" "/w14546" "/w14263" "/w14547" "/w14549" "/w14555" "/w14619" "/w14640")
list(APPEND MSVC_ADD_CXX_FLAGS "/w14826" "/w14905" "/w14906" "/w14928" "/EHsc")


list(APPEND GCC_ADD_CXX_FLAGS "-Wall -Wextra" "-Wshadow" "-Wnon-virtual-dtor" "-pedantic" "-Wold-style-cast" "-Wcast-align" "-Wunused")
list(APPEND GCC_ADD_CXX_FLAGS "-Woverloaded-virtual" "-Wpedantic" "-Wsign-conversion" "-Wmisleading-indentation" "-Wduplicated-cond")
list(APPEND GCC_ADD_CXX_FLAGS "-Wduplicated-branches" "-Wlogical-op" "-Wnull-dereference" "-Wuseless-cast" "-Wdouble-promotion")
list(APPEND GCC_ADD_CXX_FLAGS "-Wlifetime")


include(CheckCXXCompilerFlag)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    foreach(CXX_FLAG ${MSVC_ADD_CXX_FLAGS})
        check_cxx_compiler_flag(${CXX_FLAG} HAS_CXX_FLAG_${CXX_FLAG})
        if (HAS_CXX_FLAG_${CXX_FLAG})
            message("Adding compiler flag ${CXX_FLAG}")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAG}")
        endif()
    endforeach()
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    foreach(CXX_FLAG ${GCC_ADD_CXX_FLAGS})
        check_cxx_compiler_flag(${CXX_FLAG} HAS_CXX_FLAG_${CXX_FLAG})
        if (HAS_CXX_FLAG_${CXX_FLAG})
            message("Adding compiler flag ${CXX_FLAG}")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAG}")
        endif()
    endforeach()
    if(DEFINED ENV{ENABLE_COVERITY_SCAN})
        message("Enabling coverage build")
        add_compile_options(-fprofile-arcs -ftest-coverage -O0)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
    endif()
endif()


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
set(CONAN_LIBCXX ${CONAN_SETTINGS_COMPILER_LIBCXX})
conan_basic_setup(NO_OUTPUT_DIRS)


add_executable(lfQueueTest src/tests/mainTests.cpp
                           src/tests/basic.cpp 
                           src/tests/mtTests.cpp)

target_include_directories(lfQueueTest PRIVATE src/tests
                                               src/lfQueue)

                           
target_link_libraries(lfQueueTest ${CONAN_LIBS})

set_property(TARGET lfQueueTest PROPERTY CXX_STANDARD 17)
set_property(TARGET lfQueueTest PROPERTY CXX_STANDARD_REQUIRED ON)
