cmake_minimum_required(VERSION 3.8)
project(ucl_server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp tools/UCLRecieve.h tools/UCLRecieve.cpp)
add_executable(ucl_server ${SOURCE_FILES})
include_directories(
        /usr/share/ucl/include
)
target_link_libraries(ucl_server /usr/share/ucl/lib/libUCL_CPP_ZC.so)
target_link_libraries(ucl_server ssl crypto mysqlclient)

find_package(Threads REQUIRED)
target_link_libraries(ucl_server Threads::Threads)