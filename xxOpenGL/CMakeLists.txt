cmake_minimum_required(VERSION 3.30)
include_directories("../")
include_directories("D:/dulred/dev/3rdlibs/done/glfw-3.4/include")
include_directories("D:/dulred/dev/3rdlibs/done/glad-3.3/include")
link_directories("D:/dulred/dev/3rdlibs/done/glfw-3.4/lib")
add_executable(xxOpenGL "xxOpenGL.cpp" "xxOpenGL.h" )
target_link_libraries(xxOpenGL glfw3 xxGL)