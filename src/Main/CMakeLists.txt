cmake_minimum_required(VERSION 3.0)
project(Main CXX)

file(GLOB CPP_FILES
"*.cpp"
)

include_directories(${PROJECT_NAME}
    PUBLIC "${CMAKE_HOME_DIRECTORY}/include"
    PUBLIC "${CMAKE_HOME_DIRECTORY}/lib/json"
)

add_executable(${PROJECT_NAME} ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} Common Math Engine Render Resource Platform ${OPENGL_LIBRARIES} )

