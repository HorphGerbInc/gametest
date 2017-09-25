#
# https://stackoverflow.com/questions/16398937/cmake-and-finding-other-projects-and-their-dependencies
#
cmake_minimum_required(VERSION 3.0)
project(Jerobins)

# C++ properties
set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #.

# Find modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")

# Output directories
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Include folders
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/lib/json")
include_directories("${PROJECT_SOURCE_DIR}/lib/glad/include")
include_directories("${PROJECT_SOURCE_DIR}/lib/irrXML/include")

# Include libraries
find_package(ASSIMP REQUIRED)
IF ( ASSIMP_FOUND )
    LINK_LIBRARIES ( ${ASSIMP_LIBRARIES} )
ENDIF ( ASSIMP_FOUND)     

find_package ( OpenGL REQUIRED )
if ( OPENGL_FOUND )
    INCLUDE_DIRECTORIES ( ${OPENGL_INCLUDE_DIR} )
    LINK_LIBRARIES ( ${OPENGL_LIBRARIES} )
endif( OPENGL_FOUND )

find_package(IRRXML REQUIRED)
if ( IRRXML_FOUND )
    LINK_LIBRARIES ( ${IRRXML_LIBRARIES} )
ENDIF ( IRRXML_FOUND)

# if linux
if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS -msse4.1)

    FIND_PACKAGE ( X11 REQUIRED )
    IF ( X11_FOUND )
          INCLUDE_DIRECTORIES ( ${X11_INCLUDE_DIR} )
          LINK_LIBRARIES ( ${X11_LIBRARIES} )
    ENDIF ( X11_FOUND )

endif()


# add projects

# External first
add_subdirectory(lib/glad)

# Add in order of dependency
add_subdirectory(src/Common)
add_subdirectory(src/Math)
add_subdirectory(src/Resource)
add_subdirectory(src/Platform)
add_subdirectory(src/Render)
add_subdirectory(src/Engine)
add_subdirectory(src/Main)

file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY models DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# Tests
enable_testing ()
add_subdirectory(test/Common)
add_subdirectory(test/Math)
add_subdirectory(test/Platform)
add_subdirectory(test/Resource)

add_test(NAME Common COMMAND CommonTests)
