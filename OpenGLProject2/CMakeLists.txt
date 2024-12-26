cmake_minimum_required(VERSION 3.5)

project(OpenGLProject2)

add_executable(OpenGLProject2 main.c)

target_link_libraries(OpenGLProject2 glad glfw3 GL m)
