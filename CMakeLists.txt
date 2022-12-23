cmake_minimum_required(VERSION 3.0.0)
project(yaadpcml VERSION 0.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(include)
file(GLOB TARGET_SRC "./src/*.cpp" )
add_executable(adpcm 
    ${TARGET_SRC}
    include/adpcm.h)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
