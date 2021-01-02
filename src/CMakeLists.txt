cmake_minimum_required(VERSION 3.0)

set(LIB SSG)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *.h *.hpp *.cpp)

add_library(${LIB} SHARED ${SOURCES})

# target_link_libraries(${LIB} Threads::Threads)
