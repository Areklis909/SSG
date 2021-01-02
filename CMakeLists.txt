cmake_minimum_required(VERSION 3.0)

project(SSG VERSION 1.0.0 DESCRIPTION "Simple Scatter-Gather library")

set(PROJECT_VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

set(NAME SSG)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(src)

set_target_properties(${NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${NAME} PROPERTIES SOVERSION 1)

file(GLOB_RECURSE INC LIST_DIRECTORIES false "*.h" "*.hpp")

set_target_properties(SSG PROPERTIES PUBLIC_HEADER "${INC}")

configure_file(${NAME}.pc.in ${NAME}.pc @ONLY)

target_include_directories(${NAME} PRIVATE include)
target_include_directories(${NAME} PRIVATE src)

include(GNUInstallDirs)

install(TARGETS ${NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ssg)

if(BUILD_TEST)
    add_subdirectory(test)
endif()