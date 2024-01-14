cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${VENDOR_DIR}
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/Glad)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/GLFW)

add_compile_definitions(GLFW_INCLUDE_NONE)

file(GLOB SOURCES ${SRC_DIR}/*.cpp)

add_executable(main ${SOURCES})
target_link_libraries(main Glad glfw3 opengl32)

set_target_properties(main PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)
