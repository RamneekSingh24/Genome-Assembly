cmake_minimum_required(VERSION 3.19)
project(genome_assembly_de_brujin_graph)

set(CMAKE_CXX_STANDARD 14)

add_executable(genome_assembly_de_brujin_graph main.cpp)
add_executable(puzzle-assembly puzzle-assembly.cpp)
add_executable(eulerian-path eulerian-path.cpp)
add_compile_definitions(MYPC)