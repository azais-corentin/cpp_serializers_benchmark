#pragma once

#include "common/types.h"

#include <cstddef>
#include <span>
#include <vector>

struct alpaca_benchmark {
    struct MonsterWrapperInput {
        MonsterWrapperInput(std::vector<BenchmarkTypes::Monster> const &outside_monsters)
            : monsters{outside_monsters} {}

        std::vector<BenchmarkTypes::Monster> const &monsters;
    };

    std::vector<uint8_t> serialize(MonsterWrapperInput const &input);

    std::vector<BenchmarkTypes::Monster> deserialize(std::span<const uint8_t> input);
};
