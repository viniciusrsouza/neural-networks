cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  core
  VERSION 0.0.1
  DESCRIPTION "Core library with opengl and windowing"
  LANGUAGES CXX
)

file (GLOB_RECURSE SOURCES "*.cpp")
file (GLOB_RECURSE PRIMITIVE_SOURCES "primitives/*.cpp")
file (GLOB_RECURSE HEADERS "*.h")
file (GLOB_RECURSE PRIMITIVE_HEADERS "primitives/*.h")

add_library(
  core STATIC
  ${PRIMITIVE_SOURCES} ${PRIMITIVE_HEADERS}
  ${SOURCES} ${HEADERS}
)

target_include_directories(
  core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set_target_properties(
  core PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER "core.h"
)

target_link_libraries(core glm glfw glad)