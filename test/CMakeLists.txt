cmake_minimum_required(VERSION 3.0)

set(TARGET test)

set(SRC main.cpp)

add_executable(${TARGET} ${SRC})

find_library(ssg_location NAMES libSSG.so)

target_link_libraries(${TARGET} ${ssg_location} Threads::Threads)
