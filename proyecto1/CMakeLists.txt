#define minumum CMake version
cmake_minimum_required (VERSION 2.6)

#define the project name
project (Proyect_1)

find_package( OpenCV REQUIRED )

#add executable to build environment
add_executable(proyect1 calibrate_Proyection.cpp)

#copy executable to bin directory
install (TARGETS proyect1 DESTINATION bin)

#import the library of openCV 
target_link_libraries( proyect1 ${OpenCV_LIBS} )