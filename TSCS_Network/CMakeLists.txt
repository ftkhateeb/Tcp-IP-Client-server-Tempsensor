cmake_minimum_required(VERSION 3.19)
project(TSCS_Network)
file(GLOB SOURCES src/* src/*/* src/*/*/*)
add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} 
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/>  
)