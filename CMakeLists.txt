cmake_minimum_required(VERSION 2.8)
project( Terimg )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable( terimg main.cpp
                       converter.cpp
              )
set_property(TARGET terimg PROPERTY CXX_STANDARD 17)              
target_link_libraries( terimg ${OpenCV_LIBS} )

