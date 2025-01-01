# Sets minimum required version
cmake_minimum_required(VERSION 3.5)

# Project name
project(Excercises)

# Compile commands to be read by the LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Creates the executable using the project's name
add_executable(${PROJECT_NAME} main.c)

# Creates a macro based off of the project's name to be used in the program
target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_NAME_MACRO="${PROJECT_NAME}")

# Adds library source code
add_library(Shader src/shader.c)

# Indexes library include directories
target_include_directories(Shader PUBLIC include/)

# Links all external libraries
target_link_libraries(${PROJECT_NAME} glad glfw3 GL m Shader cglm)
