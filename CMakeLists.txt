cmake_minimum_required(VERSION 2.8)

project(Threaded_boids)

FIND_PACKAGE(OpenMP REQUIRED)
message(STATUS $ENV{OPENMP_FOUND})
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(library ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11 -pthread")

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY})

add_subdirectory(glfw)
include_directories(glfw/include)

add_subdirectory(cpp_threading)
add_subdirectory(cuda)
