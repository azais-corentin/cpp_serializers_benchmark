#pragma once

#include "common/types.h"

#include <cstddef>
#include <span>
#include <vector>

struct bitsery_unsafe_read {
    std::vector<std::byte> serialize(std::span<const BenchmarkTypes::Monster> input);

    std::vector<BenchmarkTypes::Monster> deserialize(std::span<const std::byte> input);
};
