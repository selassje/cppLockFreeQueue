lcov -c -d "CMakeFiles/lfQueueTest.dir/src" --include */src/lfQueue* --include */src/tests* --output-file main_coverage.info
genhtml main_coverage.info --demangle-cpp --output-directory lcovReport
