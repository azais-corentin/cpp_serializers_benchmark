// MIT License
//
// Copyright (c) 2017 Mindaugas Vinkelis
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "alpaca.hh"
#include "bitsery_brief_syntax.hh"
#include "bitsery_general.hh"
#include "flatbuffers.hh"
#include "memcpy.hh"
#include "zpp_bits.hh"
#include "zpp_bits_fixed.hh"

#include <fmt/format.h>

#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

template <typename Library> void serialization(ankerl::nanobench::Bench &serialization, std::string const &name) {
    Library implementation;

    const auto monsters = BenchmarkTypes::createMonsters(MONSTERS_COUNT);

    serialization.run(name, [&] {
        const auto output = implementation.serialize(monsters);
        ankerl::nanobench::doNotOptimizeAway(output);
    });
}

template <typename Library> void deserialization(ankerl::nanobench::Bench &deserialization, std::string const &name) {
    Library implementation;

    const auto monsters            = BenchmarkTypes::createMonsters(MONSTERS_COUNT);
    const auto serialized_monsters = implementation.serialize(monsters);

    deserialization.run(name, [&] {
        const auto output = implementation.deserialize(serialized_monsters);
        ankerl::nanobench::doNotOptimizeAway(output);
    });
}

int main() {
    using namespace std::chrono_literals;

    ankerl::nanobench::Bench serialization, deserialization;
    serialization //
        .title("Serialization")
        .relative(true)
        .minEpochIterations(1000);

    deserialization //
        .title("Deserialization")
        .relative(true)
        .minEpochIterations(1000);

    ::serialization<zpp_bits_fixed>(serialization, "zpp_bits_fixed");
    ::serialization<zpp_bits>(serialization, "zpp_bits");
    ::serialization<alpaca_benchmark>(serialization, "alpaca");
    ::serialization<bitsery_general>(serialization, "bitsery_general");
    ::serialization<bitsery_brief_syntax>(serialization, "bitsery_brief_syntax");
    ::serialization<flatbuffers_benchmark>(serialization, "flatbuffers");
    ::serialization<memcpy_benchmark>(serialization, "memcpy");

    ::deserialization<zpp_bits_fixed>(deserialization, "zpp_bits_fixed");
    ::deserialization<zpp_bits>(deserialization, "zpp_bits");
    ::deserialization<alpaca_benchmark>(deserialization, "alpaca");
    ::deserialization<bitsery_general>(deserialization, "bitsery_general");
    ::deserialization<bitsery_brief_syntax>(deserialization, "bitsery_brief_syntax");
    // ::deserialization<memcpy_benchmark>(deserialization, "memcpy"); //crashes*/

    return 0;
}
