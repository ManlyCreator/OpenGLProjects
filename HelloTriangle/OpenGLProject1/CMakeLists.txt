cmake_minimum_required(VERSION 3.5)

project(OpenGLProject1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(OpenGLProject1 main.c)

target_link_libraries(OpenGLProject1 glad glfw3 GL m)
