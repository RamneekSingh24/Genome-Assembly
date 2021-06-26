cmake_minimum_required(VERSION 3.19)
project(Genome_Assembly_Faces_Real_Sequencing_Data)

set(CMAKE_CXX_STANDARD 14)

add_executable(Genome_Assembly_Faces_Real_Sequencing_Data main.cpp)

add_executable(circulation circulation.cpp)

add_executable(optimal-k-mer optimal-k-mer.cpp)

add_executable(finding-bubbles finding-bubbles.cpp)

add_executable(tip-removal tip-removal.cpp)

add_executable(genome-assembly1 genome-assembly1.cpp)


add_compile_definitions(MYPC)