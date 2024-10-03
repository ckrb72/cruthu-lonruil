cmake_minimum_required(VERSION 3.12)

project(cruthu-lonruil)

find_package(OpenGL REQUIRED)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(DEPS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/dependencies/include")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(CMAKE_CXX_STANDARD 17)
include_directories(${OPENGL_INCLUDE_DIRS} ${DEPS_INCLUDE_DIR} ${INCLUDE_DIR})

# Don't build docs
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")

# Don't really know what this does
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(glfw)

file(GLOB_RECURSE SRC_CXX_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SRC_C_FILES "${SOURCE_DIR}/*.c")

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

add_executable(cruthu-lonruil ${SRC_CXX_FILES} ${SRC_C_FILES})
target_link_libraries(cruthu-lonruil ${OPENGL_LIBRARIES} glfw)

if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT)
    endif()
endif()