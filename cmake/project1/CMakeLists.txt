cmake_minimum_required(VERSION 2.8)

project(project1 C)

add_definitions(-g -o2 -fsigned-char -Wall -Werror)

add_executable(simple main.c)
