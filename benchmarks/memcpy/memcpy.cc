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

#include "memcpy.hh"

std::vector<std::byte> memcpy_benchmark::serialize(std::span<const BenchmarkTypes::Monster> input) {
    std::vector<std::byte> output(input.size_bytes());
    memcpy(output.data(), input.data(), input.size_bytes());

    return output;
}

std::vector<BenchmarkTypes::Monster> memcpy_benchmark::deserialize(std::span<const std::byte> input) {
    const std::size_t size = input.size_bytes() / sizeof(BenchmarkTypes::Monster);

    std::vector<BenchmarkTypes::Monster> output(size);
    output.resize(size);
    memcpy(output.data(), input.data(), input.size_bytes());

    return output;
}
