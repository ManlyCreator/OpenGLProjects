cmake_minimum_required(VERSION 3.5)

project(Pong)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.c)

target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT="${PROJECT_NAME}")

add_library(Shader src/shader.c)

target_include_directories(Shader PUBLIC include/)

target_link_libraries(${PROJECT_NAME} glad glfw3 GL cglm Shader m)
