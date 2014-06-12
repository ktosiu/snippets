aux_source_directory(. ${PROJECT_NAME}_TEST_SRC)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/test)

add_executable(${PROJECT_NAME}_test ${${PROJECT_NAME}_TEST_SRC})

target_link_libraries(${PROJECT_NAME}_test 
    skeleton
    ${GTEST_LIBRARIES})

add_dependencies(${PROJECT_NAME}_test skeleton)

set(SKELETON_TEST_EXECUTABLE ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}_test)
add_test(${PROJECT_NAME}_test ${SKELETON_TEST_EXECUTABLE})
