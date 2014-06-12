set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(MODUEL_NAME money)

aux_source_directory(. LIB_MODULE_SRC)
add_library(${MODUEL_NAME} STATIC ${LIB_MODULE_SRC})
target_link_libraries(${MODUEL_NAME} pthread)
set_target_properties(${MODUEL_NAME} PROPERTIES OUTPUT_NAME "${MODUEL_NAME}" PREFIX "lib")
