cmake_minimum_required(VERSION 3.20)

include(ExternalProject)

# Vcpkg as a submodule
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file")

# Project
project(cpp_serializers_benchmark)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported LANGUAGES C CXX)

# Sets the compilation options for the target
function(target_set_options target)
  # C++20
  target_compile_features(${target} PUBLIC cxx_std_20)
  set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
  # Enable Link Time Optimization if available
  if(ipo_supported)
    set_target_properties(${target} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()
  # Warnings
  target_compile_options(${target} PRIVATE
      $<$<CXX_COMPILER_ID:MSVC>:/W4> # MSVC
      $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic> # Not MSVC
  )
endfunction()

# Common
add_subdirectory(common)

# Benchmarks
add_subdirectory(benchmarks)

# Executable
add_subdirectory(src)
