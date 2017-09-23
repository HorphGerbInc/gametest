cmake_minimum_required(VERSION 3.0)
project(Platform CXX)

if(CMAKE_COMPILER_IS_GNUCXX)
SET(CMAKE_CXX_FALGS -msse4.1 -m64)
endif()

file(GLOB_RECURSE CPP_FILES
"*.cpp"
)

file(GLOB_RECURSE HPP_FILES
"${CMAKE_HOME_DIRECTORY}/include/${PROJECT_NAME}/*.hpp"
)

include_directories(${PROJECT_NAME}
    PUBLIC "${CMAKE_HOME_DIRECTORY}/include"
    PUBLIC "${CMAKE_HOME_DIRECTORY}/lib/json"
)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${HPP_FILES})

set_target_properties(${PROJET_NAME}
    PROPERTIES POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
