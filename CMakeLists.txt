cmake_minimum_required(VERSION 3.15.0)

project(polynomial VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(polynomial main.c polynomial.c)
