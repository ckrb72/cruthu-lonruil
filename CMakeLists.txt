cmake_minimum_required(VERSION 3.13)

project(cruthu-lonruil)

find_package(OpenGL REQUIRED)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(DEPS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/dependencies/include")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/assimp/include")
set(CMAKE_CXX_STANDARD 17)
include_directories(${OPENGL_INCLUDE_DIRS} ${DEPS_INCLUDE_DIR} ${INCLUDE_DIR})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)


add_subdirectory(glfw)
add_subdirectory(assimp)

file(GLOB_RECURSE SRC_CXX_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SRC_C_FILES "${SOURCE_DIR}/*.c")

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

add_executable(cruthu-lonruil ${SRC_CXX_FILES} ${SRC_C_FILES})
target_link_libraries(cruthu-lonruil ${OPENGL_LIBRARIES} glfw assimp)

if( MSVC )
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT)
endif()