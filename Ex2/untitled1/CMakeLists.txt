cmake_minimum_required(VERSION 3.17)
project(untitled1 C)

add_compile_options(-Wall -Wextra)

set(CMAKE_C_STANDARD 90)

add_executable(untitled1 main.c;
        auxiliares.c;
        estruturas.c;
        )