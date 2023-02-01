cmake_minimum_required(VERSION 3.8)
project(solver VERSION 0.1.0 LANGUAGES CXX)
add_executable(solver solver.cpp parameters.cpp mesh.cpp explicit.cpp export.cpp)
target_compile_features(solver PUBLIC cxx_std_17)
