add_library(hello SHARED hello.cpp)
add_library(hello_static STATIC hello.cpp)

set_target_properties(hello_static PROPERTIES OUTPUT_NAME "hello")
set_target_properties(hello PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

install(TARGETS hello hello_static
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

INSTALL(FILES hello.h DESTINATION include)

