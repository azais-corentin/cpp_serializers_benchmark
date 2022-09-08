# Find zpp_bits library
find_path(ZPP_BITS_INCLUDE_DIRS "zpp_bits.h")

# zpp_bits
add_library(zpp_bits)
target_sources(zpp_bits PRIVATE zpp_bits.hh zpp_bits.cc)
target_set_options(zpp_bits)
target_link_libraries(zpp_bits PRIVATE common)
target_include_directories(zpp_bits PRIVATE ${ZPP_BITS_INCLUDE_DIRS})
target_include_directories(zpp_bits PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# zpp_bits_fixed
add_library(zpp_bits_fixed)
target_sources(zpp_bits_fixed PRIVATE zpp_bits_fixed.hh zpp_bits_fixed.cc)
target_set_options(zpp_bits_fixed)
target_link_libraries(zpp_bits_fixed PRIVATE common)
target_include_directories(zpp_bits_fixed PRIVATE ${ZPP_BITS_INCLUDE_DIRS})
target_include_directories(zpp_bits_fixed PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
