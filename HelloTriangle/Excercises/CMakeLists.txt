cmake_minimum_required(VERSION 3.5)

project(Excercises)

add_executable(Excercises main.c)

target_link_libraries(Excercises glad glfw3 GL m)
