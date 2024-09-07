cmake_minimum_required(VERSION 3.22.1)
project(lab2_4 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab2_4 main.c medicine.c medicine.h repository_medicine.c repository_medicine.h service_medicine.c service_medicine.h)
