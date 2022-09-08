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

#include "zpp_bits.hh" // Ours

#include "zpp_bits.h" // External library

#include <span>

std::vector<std::byte> zpp_bits::serialize(std::span<const BenchmarkTypes::Monster> input) {
    auto [data, out] = zpp::bits::data_out();

    if (zpp::bits::success(out(input))) { return data; }

    return {};
}

std::vector<BenchmarkTypes::Monster> zpp_bits::deserialize(std::span<const std::byte> input) {
    zpp::bits::in in{input};

    std::vector<BenchmarkTypes::Monster> output;

    if (zpp::bits::success(in(output))) { return output; }

    return {};
}
