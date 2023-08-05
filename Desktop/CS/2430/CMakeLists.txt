cmake_minimum_required(VERSION 3.24)
project(2430)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall -Werror -pedantic)

add_executable(2430 pg5/main.cpp pg5/CovidDB.cpp)
