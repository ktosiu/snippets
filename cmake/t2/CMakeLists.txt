project(hello)
add_subdirectory(src)

install(FILES COPYRIGHT README DESTINATION share/doc/cmake/t2)
install(PROGRAMS run.sh DESTINATION bin)
install(DIRECTORY doc/ DESTINATION share/doc/cmake/t2)
