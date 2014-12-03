add_executable(main main.cpp)
include_directories(/tmp/hello/include)
link_directories(/tmp/hello/lib)
target_link_libraries(main libhello.a)
