#pragma once

#include "common/types.h"

#include <array>
#include <cstddef>
#include <span>
#include <vector>

struct zpp_bits_fixed {
    std::span<std::byte> serialize(std::span<const BenchmarkTypes::Monster> input);

    std::span<BenchmarkTypes::Monster> deserialize(std::span<const std::byte> input);

  private:
    std::array<std::byte, 150000> data_;
    std::vector<BenchmarkTypes::Monster> output_;
};
