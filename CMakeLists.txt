cmake_minimum_required(VERSION 2.8)
project(private_protocol_c)
set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES src/*.c src/*.h)

message(---Debug Echo---)
foreach(src_file ${SOURCES})
    message(src_file=${src_file})
endforeach()

add_executable(private_protocol_c ${SOURCES})
