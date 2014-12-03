add_executable(curltest main.cpp)

# Simple method to include curl
#include_directories(/usr/include)
#target_link_libraries(curltest curl)

# Use find_package
find_package(CURL)
if(CURL_FOUND)
  include_directories(${CURL_INCLUDE_DIR})
  target_link_libraries(curltest ${CURL_LIBRARY})
else(CURL_FOUND)
  message(FATAL_ERROR "curl library not found")
endif(CURL_FOUND)
