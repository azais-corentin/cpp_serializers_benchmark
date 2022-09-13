#pragma once

#include "common/types.h"

#include <cstddef>
#include <span>
#include <vector>

struct bitsery_brief_syntax {
    std::vector<std::byte> serialize(std::span<const BenchmarkTypes::Monster> input);

    std::vector<BenchmarkTypes::Monster> deserialize(std::vector<std::byte> const &input);
};
