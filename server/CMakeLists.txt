cmake_minimum_required(VERSION 3.5)
project(server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp conn_queue.cpp conn_queue.h
        server.cpp server.h define.h
        smart_thing.cpp smart_thing.h
        server_sock.cpp server_sock.h)

add_executable(server ${SOURCE_FILES})
target_link_libraries(server ev pthread)