cmake_minimum_required(VERSION 3.5)

project(Excercises)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_subdirectory(Shader/)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} glad glfw3 GL m Shader)
