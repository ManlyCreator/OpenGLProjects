# Minimum CMake
cmake_minimum_required(VERSION 3.5)

# Project Name
project(ProceduralShapes)

# Project Settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compile Executable
add_executable(${PROJECT_NAME} main.c)

# Compile Libraries
add_library(Shader src/shader.c)
add_library(Texture src/texture.c)
add_library(Sphere src/sphere.c)
add_library(MatrixStack src/matrixStack.c)
add_library(Shape src/shape.c)
add_library(Cube src/cube.c)
add_library(Pyramid src/pyramid.c)
set(Dependencies Shader Texture Sphere MatrixStack Shape Cube Pyramid)

# Include Directory
include_directories(include/)

# Creates a PROJECT Macro
target_compile_definitions(${PROJECT_NAME} PUBLIC PROJECT="${PROJECT_NAME}")

# Links Libraries
target_link_libraries(${PROJECT_NAME} glad glfw3 GL m ${Dependencies})
