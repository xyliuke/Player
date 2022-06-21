cmake_minimum_required(VERSION 3.22)
project(MacOpenGLDemo)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

MESSAGE(${CMAKE_HOST_SYSTEM_NAME})
MESSAGE(${CMAKE_SYSTEM_PROCESSOR})

function(AppleSiliconLib)
    MESSAGE(DEBUG "Apple Silicon CPU Platform")

    #GLFW
    INCLUDE_DIRECTORIES(Lib/GLFW/include)
    LINK_DIRECTORIES(Lib/GLFW/lib-arm64)

    #GLEW
    INCLUDE_DIRECTORIES(Lib/glew/include)
    LINK_DIRECTORIES(Lib/glew/lib-arm64)
endfunction()

function(AppleX64Lib)
    MESSAGE(DEBUG "Apple X86_64 CPU Platform")

    #GLFW
    INCLUDE_DIRECTORIES(Lib/GLFW/include)
    LINK_DIRECTORIES(Lib/GLFW/lib-x86_64)

    #GLEW
    INCLUDE_DIRECTORIES(Lib/glew/include)
    LINK_DIRECTORIES(Lib/glew/lib-x86_64)
endfunction()

if (APPLE)
    if (CMAKE_SYSTEM_PROCESSOR MATCHES arm64)
        AppleSiliconLib()
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES x86_64)
        AppleX64Lib()
    endif ()
endif ()

AUX_SOURCE_DIRECTORY(. SRCS)

add_executable(MacOpenGLDemo ${SRCS} )

TARGET_LINK_LIBRARIES(MacOpenGLDemo GLEW)
TARGET_LINK_LIBRARIES(MacOpenGLDemo glfw3)

if (APPLE)
    TARGET_LINK_LIBRARIES(MacOpenGLDemo "-framework OpenGL")
    TARGET_LINK_LIBRARIES(MacOpenGLDemo "-framework CoreFoundation")
    TARGET_LINK_LIBRARIES(MacOpenGLDemo "-framework CoreGraphics")
    TARGET_LINK_LIBRARIES(MacOpenGLDemo "-framework IOKit")
    TARGET_LINK_LIBRARIES(MacOpenGLDemo "-framework AppKit")
endif ()