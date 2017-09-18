cmake_minimum_required(VERSION 3.0)
project(Common CXX)

file(GLOB CPP_FILES
"*.cpp"
)

file(GLOB HPP_FILES
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

target_link_libraries(${PROJECT_NAME})
