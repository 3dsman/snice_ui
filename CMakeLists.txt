project(snice_ui)
cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

include_directories(src)

add_definitions(-std=c++11 -ggdb -O3)

aux_source_directory(. SRC_LIST)

FILE(GLOB_RECURSE SRC_LIST RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
FILE(GLOB_RECURSE HDR_LIST RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_executable(${PROJECT_NAME} test_UI.cpp ${SRC_LIST} test_UI.h ${HDR_LIST})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})

