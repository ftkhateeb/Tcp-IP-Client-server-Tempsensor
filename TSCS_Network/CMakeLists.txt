cmake_minimum_required(VERSION 3.19)
project(TSCS_Network)

find_package(Boost 1.79.0 REQUIRED)
file(GLOB SOURCES src/* src/*/* src/*/*/*)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/>
        ${Boost_INCLUDE_DIRS} 
        
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${Boost_LIBRARIES}

)
if(MINGW)
  target_link_libraries(${PROJECT_NAME}
    PRIVATE
        -lws2_32 -lwsock32)
endif()