cmake_minimum_required(VERSION 3.5)
project(client)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp)

add_executable(client ${SOURCE_FILES})
target_link_libraries(client ev pthread)