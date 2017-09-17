cmake_minimum_required(VERSION 3.0)

project(Resource CXX)

file(GLOB CPP_FILES
"*.cpp"
)

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

include_directories(${PROJECT_NAME}
    PUBLIC "${CMAKE_HOME_DIRECTORY}/include"
    PUBLIC "${CMAKE_HOME_DIRECTORY}/lib/json"
)

find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} )
