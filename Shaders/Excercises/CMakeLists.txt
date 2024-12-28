cmake_minimum_required(VERSION 3.5)

project(Excercises)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.c)

add_subdirectory(Shader)

target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw3 GL m Shader)
