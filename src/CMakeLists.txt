cmake_minimum_required(VERSION 3.0)

set(LIB SSG)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *.h *.hpp *.cpp)

add_library(${LIB} SHARED ${SOURCES})

# add_executable(${BINARY} ${TEST_SOURCES})

# add_test(NAME ${BINARY} COMMAND ${BINARY})

# set(LIBS CommandLineParser ImageEncryptor ImageHandler PixelStrategy gtest gmock)

# target_link_libraries(${BINARY} PUBLIC ${LIBS})