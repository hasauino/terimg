cmake_minimum_required(VERSION 2.8)
project( Terimg )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} ./include)

add_executable( terimg main.cpp
                       converter.cpp
              )
target_link_libraries( terimg ${OpenCV_LIBS} )
