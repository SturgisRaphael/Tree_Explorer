cmake_minimum_required(VERSION 3.3)

project(Test)

project(Example)

include(CTest)
enable_testing()

add_subdirectory(lib/googletest-master)

include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(runUnitTests gtest.cpp
		utils/FileManager_test.cpp structures/Tree_test.cpp Algorithms/LinearProgrammingSolver_test.cpp glpk/glpk_interface_test.cpp)

target_link_libraries(runUnitTests gtest core)