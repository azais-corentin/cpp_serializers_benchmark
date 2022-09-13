#pragma once

#include "common/types.h"

#include <cstddef>
#include <span>
#include <vector>

struct bitsery_general {
    std::vector<std::byte> serialize(std::span<const BenchmarkTypes::Monster> input);

    std::vector<BenchmarkTypes::Monster> deserialize(const std::vector<std::byte> &input);
};
