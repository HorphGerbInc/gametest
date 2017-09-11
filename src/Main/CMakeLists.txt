cmake_minimum_required(VERSION 3.0)

project(Main CXX)

file(GLOB CPP_FILES
"*.cpp"
)

include_directories(${PROJECT_NAME}
    PUBLIC "${CMAKE_HOME_DIRECTORY}/include"
    PUBLIC "${CMAKE_HOME_DIRECTORY}/lib/json"
)


target_link_libraries(${PROJECT_NAME} Common Math Render Resource Engine ${OPENGL_LIBRARIES} )

add_executable(execute ${CPP_FILES})
