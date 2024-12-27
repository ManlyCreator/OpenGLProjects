cmake_minimum_required(VERSION 3.10)

project(OpenGLTemplate)

add_executable(OpenGLTemplate main.c)

target_link_libraries(OpenGLTemplate glad glfw3 GL m)
