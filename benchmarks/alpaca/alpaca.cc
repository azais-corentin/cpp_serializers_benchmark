#include "alpaca.hh"

#include "alpaca/alpaca.h"

struct MonsterWrapperOutput {
    std::vector<BenchmarkTypes::Monster> monsters;
};

std::vector<uint8_t> alpaca_benchmark::serialize(const MonsterWrapperInput &input) {
    std::vector<uint8_t> output;

    const auto bytes_written = alpaca::serialize(input, output);

    if (bytes_written > 0) { return output; }

    return {};
}

std::vector<BenchmarkTypes::Monster> alpaca_benchmark::deserialize(std::span<const uint8_t> input) {
    // std::vector<BenchmarkTypes::Monster> output;

    std::error_code ec;
    auto output = alpaca::deserialize<MonsterWrapperOutput>(input, ec);

    if (!ec) { return {output.monsters.begin(), output.monsters.end()}; }

    return {};
}
