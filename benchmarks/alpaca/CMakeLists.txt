include(FetchContent)

FetchContent_Declare(alpaca
    GIT_REPOSITORY https://github.com/p-ranav/alpaca.git
    GIT_TAG        v0.2.0
)
FetchContent_MakeAvailable(alpaca)

# alpaca
add_library(alpaca_benchmark)
target_sources(alpaca_benchmark PRIVATE alpaca.hh alpaca.cc)
target_set_options(alpaca_benchmark)
target_link_libraries(alpaca_benchmark PRIVATE common)
target_include_directories(alpaca_benchmark PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(alpaca_benchmark PRIVATE alpaca::alpaca)
