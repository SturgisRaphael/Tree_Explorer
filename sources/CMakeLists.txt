cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

add_library(core utils/FileManager.cpp utils/FileManager.h algortihms/LinearProgrammingSolver.cpp algortihms/LinearProgrammingSolver.h)
add_executable(exec main.cpp)

target_link_libraries(exec core)


