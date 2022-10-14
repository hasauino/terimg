cmake_minimum_required(VERSION 2.8)
project( Terimg )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} ./include)

add_executable( terimg main.cpp )
target_link_libraries( terimg ${OpenCV_LIBS} )
