#
# https://stackoverflow.com/questions/16398937/cmake-and-finding-other-projects-and-their-dependencies
#
cmake_minimum_required(VERSION 3.0)
project(Jerobins)

set(CMAKE_CXX_STANDARD 14)
if(UNIX AND NOT APPLE)
set(CMAKE_CXX_FLAGS -msse4.1)

FIND_PACKAGE ( X11 REQUIRED )
IF ( X11_FOUND )
      INCLUDE_DIRECTORIES ( ${X11_INCLUDE_DIR} )
      LINK_LIBRARIES ( ${X11_LIBRARIES} )
ENDIF ( X11_FOUND )

FIND_PACKAGE ( OpenGL REQUIRED )
IF ( OPENGL_FOUND )
    INCLUDE_DIRECTORIES ( ${OPENGL_INCLUDE_DIR} )
    LINK_LIBRARIES ( ${OPENGL_LIBRARIES} )
endif( OPENGL_FOUND )

endif()

# Output directories
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Include folders
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/lib/json")

# GLEW
set(GLEW_ROOT "${CMAKE_HOME_DIRECTORY}/lib/glew")
set(GLEW_INCLUDE "${CMAKE_HOME_DIRECTORY}/lib/glew")
set(GLEW_LIB "${CMAKE_HOME_DIRECTORY}/lib/glew/lib/Release/Win32")
set(GLEW_DLL "${CMAKE_HOME_DIRECTORY}/lib/glew/bin/Release/Win32/")

# Remove 'lib' prefix for shared libraries on Windows
if (WIN32)
    set(APPEND CMAKE_SHARED_LIBRARY_PREFIX "")
    list(APPEND CMAKE_PREFIX_PATH ${GLEW_LIB} ${GLEW_INCLUDE} ${GLEW_DLL})
    list(APPEND CMAKE_LIBRARY_PATH ${GLEW_LIB} ${GLEW_INCLUDE} ${GLEW_DLL})
endif ()


add_subdirectory(src/Common)
add_subdirectory(src/Engine)
add_subdirectory(src/Math)
add_subdirectory(src/Render)
add_subdirectory(src/Resource)
add_subdirectory(src/Main)
add_subdirectory(src/Platform)


file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# Tests
enable_testing ()
add_subdirectory(test/Common)
add_subdirectory(test/Math)
add_subdirectory(test/Platform)

add_test(NAME Common COMMAND CommonTests)