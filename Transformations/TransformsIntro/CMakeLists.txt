cmake_minimum_required(VERSION 3.5)

project(TransformsIntro)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_executable(${PROJECT_NAME} main.c)

add_library(Shader src/shader.c)

target_include_directories(Shader PUBLIC include/)

target_link_libraries(${PROJECT_NAME} glad glfw3 GL m Shader cglm)
