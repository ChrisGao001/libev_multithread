cmake_minimum_required(VERSION 3.5)
project(libev_multithread)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(server)
add_subdirectory(client)

