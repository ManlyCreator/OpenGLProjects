cmake_minimum_required(VERSION 3.5)

project(VertexColors)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(VertexColors main.c)

add_subdirectory(Shader)

target_link_libraries(VertexColors PRIVATE glad glfw3 GL m Shader)
