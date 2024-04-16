cmake_minimum_required(VERSION 3.22.0)

project(DTPC)

add_executable(dtpc client.cpp)

install(TARGETS dtpc DESTINATION bin)