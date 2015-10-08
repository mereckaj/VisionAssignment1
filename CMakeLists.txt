cmake_minimum_required(VERSION 3.3)

project(VisionAssignment1)
find_package(OpenCV REQUIRED )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SOURCE_FILES Main.cpp Utils.cpp Preprocess.h Preprocess.cpp)
add_executable(VisionAssignment1 ${SOURCE_FILES})

target_link_libraries( VisionAssignment1 ${OpenCV_LIBS} )