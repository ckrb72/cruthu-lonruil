cmake_minimum_required(VERSION 3.12)

project(cruthu-lonruil)

find_package(OpenGL REQUIRED)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/dependencies/include")
set(CMAKE_CXX_STANDARD 17)
include_directories(${OPENGL_INCLUDE_DIRS} ${INCLUDE_DIR})

# Don't build docs
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")

# Don't really know what this does
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(glfw)

file(GLOB_RECURSE SRC_CXX_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SRC_C_FILES "${SOURCE_DIR}/*.c")

add_executable(cruthu-lonruil ${SRC_CXX_FILES} ${SRC_C_FILES})
target_link_libraries(cruthu-lonruil ${OPENGL_LIBRARIES} glfw)

