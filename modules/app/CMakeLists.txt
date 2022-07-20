set(SRC
  ${SRC}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/dodger.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/player.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/object_buffer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/generated_object.cpp
  PARENT_SCOPE
)

set(INC
  ${INC}
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
  PARENT_SCOPE
)