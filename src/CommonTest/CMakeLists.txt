
file(GLOB CommonTest_SRC
"*.cpp"
)

add_library(CommonTest SHARED ${CommonTest_SRC})
target_include_directories(CommonTest 
    PUBLIC "${CMAKE_HOME_DIRECTORY}/include"
    PUBLIC "${CMAKE_HOME_DIRECTORY}/lib/json"
)