cmake_minimum_required(VERSION 3.5)

project(TexturePyramids)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.c)

add_library(Shader src/shader.c)
add_library(Texture src/texture.c)
add_library(Scene src/scene.c)
add_library(Utils src/utils.c)

include_directories(include/)

target_compile_definitions(${PROJECT_NAME} PUBLIC PROJECT="${PROJECT_NAME}")

target_link_libraries(${PROJECT_NAME} glad glfw3 GL m Shader Scene Utils Texture)
