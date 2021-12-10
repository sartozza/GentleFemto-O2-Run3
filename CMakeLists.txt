cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(binFolder "${CMAKE_CURRENT_BINARY_DIR}/../install")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${binFolder}/lib)
project(GentleFemtoO2 CXX C)
enable_testing()

add_subdirectory(MakingCorrelations)

