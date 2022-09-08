add_executable(cpp_serializers_benchmark)
target_sources(cpp_serializers_benchmark PRIVATE)

target_set_options(cpp_serializers_benchmark)

target_compile_definitions(cpp_serializers_benchmark PRIVATE
    MONSTERS_COUNT=50
)

target_sources(cpp_serializers_benchmark PRIVATE
    main.cpp
    types.cpp
    uniform_distributions.h
    nanobench.h
)

# Benchmarks
target_link_libraries(cpp_serializers_benchmark PRIVATE
    common
    zpp_bits
    zpp_bits_fixed
    bitsery_general
)
