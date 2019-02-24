cmake_minimum_required(VERSION 2.8) 

#Project's name
project(Boids_cpp)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(src)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

file(
    GLOB
    source_files
    src/*.cpp
    src/*.h*
)

add_library(boids_cpp SHARED ${source_files})
add_executable(main_cpp main.cpp)
target_link_libraries(main_cpp ${GLEW_LIBRARIES} glfw boids_cpp ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
