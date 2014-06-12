# Set the project name here
set(PROJECT_NAME money)

PROJECT(${PROJECT_NAME})
cmake_minimum_required(VERSION 2.8)

find_package(GTest REQUIRED)
if(GTEST_FOUND)
    enable_testing()
    include_directories(${GTEST_INCLUDE_DIRS})
endif(GTEST_FOUND)

include_directories(include)

add_subdirectory(src)

if(GTEST_FOUND)
    add_subdirectory(test)
endif(GTEST_FOUND)
