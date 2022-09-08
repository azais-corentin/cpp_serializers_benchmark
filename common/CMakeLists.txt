cmake_minimum_required(VERSION 3.20)

add_library(common INTERFACE)

target_sources(common PUBLIC
    common/types.h
)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
