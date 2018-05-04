cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

link_libraries(
	glpk
)

add_library(core utils/FileManager.cpp utils/FileManager.h algortihms/LinearProgrammingSolver.cpp algortihms/LinearProgrammingSolver.h glpk/glpk_interface.cpp glpk/glpk_interface.h structures/Edge.h structures/Tree.h structures/Tree.h structures/Tripple.h algortihms/TreeGenerator.cpp algortihms/TreeGenerator.h)
add_executable(exec main.cpp)

target_link_libraries(exec core)


