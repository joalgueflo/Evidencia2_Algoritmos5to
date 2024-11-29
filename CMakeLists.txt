cmake_minimum_required(VERSION 3.10)
project(EvidenciaUnitTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_REQUIRED ON)

enable_testing()

add_subdirectory(test)
add_library(evidencia_lib evidencia2_helpers.cpp)
add_executable(evidencia2 evidencia2.cpp)
target_link_libraries(evidencia2 evidencia_lib)
