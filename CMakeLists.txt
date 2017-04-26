cmake_minimum_required(VERSION 3.5)
project(libev_multithread)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp src/conn_queue.cpp src/conn_queue.h src/server.cpp src/server.h src/define.h src/smart_thing.cpp src/smart_thing.h src/server_sock.cpp src/server_sock.h)

add_executable(libev_multithread ${SOURCE_FILES})
target_link_libraries(libev_multithread ev pthread)