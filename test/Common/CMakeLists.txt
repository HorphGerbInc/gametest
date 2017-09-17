
file(GLOB CPP_FILES
"*.cpp"
)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES})
target_include_directories(CommonTest 
    PUBLIC "${CMAKE_HOME_DIRECTORY}/include"
    PUBLIC "${CMAKE_HOME_DIRECTORY}/lib/json"
)