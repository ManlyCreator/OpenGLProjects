# Minimum CMake
cmake_minimum_required(VERSION 3.25)

# Project Name
project(Lighting)

# Project Settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compile Executable
add_executable(${PROJECT_NAME} main.c)

# Compile Libraries
set(Dependencies)

function(create_library library src libraryList)
  add_library(${library} src/${src})
  list(APPEND ${libraryList} ${library})
  return(PROPAGATE ${libraryList})
endfunction()

create_library(Shader shader.c Dependencies)
create_library(Texture texture.c Dependencies)
create_library(Sphere sphere.c Dependencies)
create_library(MatrixStack matrixStack.c Dependencies)
create_library(Shape shape.c Dependencies)
create_library(Cube cube.c Dependencies)
create_library(Pyramid pyramid.c Dependencies)
create_library(Torus torus.c Dependencies)
create_library(Model model.c Dependencies)
create_library(Camera camera.c Dependencies)

# Include Directory
include_directories(include/)

# Creates a PROJECT Macro
target_compile_definitions(${PROJECT_NAME} PUBLIC PROJECT="${PROJECT_NAME}")

# Links Libraries
target_link_libraries(${PROJECT_NAME} glad glfw3 GL m ${Dependencies})
