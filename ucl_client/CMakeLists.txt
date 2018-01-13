cmake_minimum_required(VERSION 3.8)
project(ucl_client)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp tools/dbHelper.cpp tools/dbHelper.h tools/UCLSend.h tools/UCLSend.cpp)
add_executable(ucl_client ${SOURCE_FILES})
include_directories(
        /usr/share/ucl/include
)
target_link_libraries(ucl_client /usr/share/ucl/lib/libUCL_CPP_ZC.so)
target_link_libraries(ucl_client ssl crypto mysqlclient)