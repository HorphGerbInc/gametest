cmake_minimum_required(VERSION 3.0)

project(Engine CXX)

file(GLOB CPP_FILES
"*.cpp"
)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC "${CMAKE_HOME_DIRECTORY}/include"
    PUBLIC "${CMAKE_HOME_DIRECTORY}/lib/json"
)