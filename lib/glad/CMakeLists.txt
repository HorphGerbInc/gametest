cmake_minimum_required(VERSION 3.0)
project(Glad CXX)

file(GLOB_RECURSE CPP_FILES
"glad.c"
)

file(GLOB_RECURSE HPP_FILES
"glad.hpp"
)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${HPP_FILES})

set_target_properties(${PROJET_NAME}
    PROPERTIES POSITION_INDEPENDENT_CODE ON
)

if(UNIX)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY} ${CMAKE_DL_LIBS})
else()
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY} )
endif()
