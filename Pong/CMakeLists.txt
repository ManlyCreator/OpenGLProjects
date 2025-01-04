cmake_minimum_required(VERSION 3.5)

project(Pong)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.c)

add_library(Shader src/shader.c)
add_library(Texture src/texture.c)
add_library(Game src/game.c)
add_library(Sprite src/sprite.c)

include_directories(include/)

target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT="${PROJECT_NAME}")

target_link_libraries(${PROJECT_NAME} glad glfw3 GL m cglm Shader Texture Game Sprite)
