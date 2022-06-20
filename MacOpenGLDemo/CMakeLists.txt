cmake_minimum_required(VERSION 3.22)
project(MacOpenGLDemo)

set(CMAKE_CXX_STANDARD 14)

#GLFW
INCLUDE_DIRECTORIES(Lib/GLFW/)
LINK_DIRECTORIES(Lib/GLFW)

add_executable(MacOpenGLDemo main.cpp)

TARGET_LINK_LIBRARIES(MacOpenGLDemo glfw3 "-framework CoreFoundation" "-framework CoreGraphics" "-framework IOKit" "-framework AppKit")
