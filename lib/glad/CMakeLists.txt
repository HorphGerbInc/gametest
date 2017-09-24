cmake_minimum_required(VERSION 3.0)
project(Glad CXX)

file(GLOB_RECURSE CPP_FILES
"*.c"
)

file(GLOB_RECURSE HPP_FILES
"*.hpp"
)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${HPP_FILES})

set_target_properties(${PROJET_NAME}
    PROPERTIES POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY})
