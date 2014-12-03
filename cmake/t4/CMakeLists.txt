project(hello)
add_subdirectory(src)
add_test(test ${PROJECT_BINARY_DIR}/src/main)
enable_testing()
