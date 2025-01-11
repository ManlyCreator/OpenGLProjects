cmake_minimum_required(VERSION 3.5)

project(ShaderRotation)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.c)

add_library(Shader src/shader.c)

include_directories(include/)

target_compile_definitions(${PROJECT_NAME} PUBLIC PROJECT="${PROJECT_NAME}")

target_link_libraries(${PROJECT_NAME} glad glfw3 GL m Shader)
