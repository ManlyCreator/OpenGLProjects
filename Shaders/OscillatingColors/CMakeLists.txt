cmake_minimum_required(VERSION 3.5)

project(OscillatingColors)

add_executable(OscillatingColors main.c)

target_link_libraries(OscillatingColors glad glfw3 GL m)
