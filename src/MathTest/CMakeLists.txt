
file(GLOB MathTest_SRC
"*.cpp"
)

add_library(MathTest STATIC ${MathTest_SRC})
target_include_directories(MathTest 
    PUBLIC "${CMAKE_HOME_DIRECTORY}/include"
    PUBLIC "${CMAKE_HOME_DIRECTORY}/lib/json"
)