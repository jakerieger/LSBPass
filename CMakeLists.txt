cmake_minimum_required(VERSION 3.30)
project(img_lsb_pass)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(img_lsb_pass main.cpp)
