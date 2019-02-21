cmake_minimum_required(VERSION 2.8)

#Project's name
project(Boids_GPUa)

find_package(CUDA REQUIRED)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11 -lcuda -lcudart")

cuda_add_library(lib_boids_cuda SHARED Boid.cpp Vector2D.cpp Flock.cpp kernel.cu)

include_directories(${CUDA_INCLUDE_DIRS}
                    ${OPENGL_INCLUDE_DIRS} 
                    ${GLUT_INCLUDE_DIRS}
                    $(GLEW_INCLUDE_DIRS)
                    /usr/local/cuda/samples/common/inc
                    )

add_executable(main_cuda main.cpp)
target_link_libraries(main_cuda lib_boids_cuda ${GLUT_LIBRARIES} 
    ${OPENGL_LIBRARIES} ${OpenCL_LIBRARY} ${CUDA_LIBRARIES}
    -lglut -lGL -lGLU -lGLEW -lpthread)
