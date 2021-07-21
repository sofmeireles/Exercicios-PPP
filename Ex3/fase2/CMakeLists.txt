cmake_minimum_required(VERSION 3.17)
project(fase2 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra)

add_executable(fase2 main.c auxiliares.c header.h estruturas.c)