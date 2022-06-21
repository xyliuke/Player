cmake_minimum_required(VERSION 3.22)
project(MacOpenGLDemo)

set(CMAKE_CXX_STANDARD 14)

#GLFW
INCLUDE_DIRECTORIES(Lib/GLFW/)
LINK_DIRECTORIES(Lib/GLFW)

#find_package(OpenGL REQUIRED)

#GLEW
INCLUDE_DIRECTORIES(/usr/local/opt/glew/include)
LINK_DIRECTORIES(/usr/local/opt/glew/lib)

aux_source_directory(. SRCS)

add_executable(MacOpenGLDemo ${SRCS} )

TARGET_LINK_LIBRARIES(MacOpenGLDemo GLEW)
TARGET_LINK_LIBRARIES(MacOpenGLDemo "-framework OpenGL")
TARGET_LINK_LIBRARIES(MacOpenGLDemo glfw3 "-framework CoreFoundation" "-framework CoreGraphics" "-framework IOKit" "-framework AppKit")
