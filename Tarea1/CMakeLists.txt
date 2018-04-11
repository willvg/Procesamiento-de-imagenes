#define minumum CMake version
cmake_minimum_required (VERSION 2.6)

#define the project name
project (showimage)

find_package( OpenCV REQUIRED )

#add executable to build environment
add_executable(showImage Image.cpp)

#copy executable to bin directory
install (TARGETS showImage DESTINATION bin)

#import the library of openCV 
target_link_libraries( showImage ${OpenCV_LIBS} )