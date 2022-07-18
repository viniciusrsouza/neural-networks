cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

project(
  glad
  VERSION 0.0.1
  LANGUAGES C
)

add_library(
  glad STATIC
  src/glad.c
)

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(
  glad PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER "glad.h"
)
