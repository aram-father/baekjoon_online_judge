cmake_minimum_required(VERSION 3.0.0)
project(sol)
add_compile_options(-std=c++11 -Wall)
add_executable(${PROJECT_NAME} sol.cc)
