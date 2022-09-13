# memcpy
add_library(memcpy)
target_sources(memcpy PRIVATE memcpy.hh memcpy.cc)
target_set_options(memcpy)
target_link_libraries(memcpy PRIVATE common)
target_include_directories(memcpy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
