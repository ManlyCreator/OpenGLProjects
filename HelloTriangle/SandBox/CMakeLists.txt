cmake_minimum_required(VERSION 3.5)

project(SandBox)

add_executable(SandBox main.c)

target_link_libraries(SandBox glad glfw3 GL m)
