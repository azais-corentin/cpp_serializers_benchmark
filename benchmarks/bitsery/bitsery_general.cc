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

#include "bitsery_general.hh"

#include <bitsery/adapter/buffer.h>
#include <bitsery/bitsery.h>
#include <bitsery/traits/string.h>
#include <bitsery/traits/vector.h>

using Buffer        = std::vector<std::byte>;
using InputAdapter  = bitsery::InputBufferAdapter<Buffer>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;

/**
 * Bitsery traits for std::span container
 */
namespace bitsery::traits {

template <typename T> struct ContainerTraits<std::span<T>> : public StdContainer<std::span<T>, true, true> {};

template <typename T> struct BufferAdapterTraits<std::span<T>> : public StdContainerForBufferAdapter<std::span<T>> {};

} // namespace bitsery::traits

namespace bitsery {

template <typename S> void serialize(S &s, BenchmarkTypes::Vec3 &o) {
    s.value4b(o.x);
    s.value4b(o.y);
    s.value4b(o.z);
}

template <typename S> void serialize(S &s, BenchmarkTypes::Weapon &o) {
    s.text1b(o.name, 10);
    s.value2b(o.damage);
}

template <typename S> void serialize(S &s, BenchmarkTypes::Monster &o) {
    s.value1b(o.color);
    s.value2b(o.mana);
    s.value2b(o.hp);
    s.object(o.equipped);
    s.object(o.pos);
    s.container(o.path, 10);
    s.container(o.weapons, 10);
    s.container1b(o.inventory, 10);
    s.text1b(o.name, 10);
}

} // namespace bitsery

std::vector<std::byte> bitsery_general::serialize(std::span<const BenchmarkTypes::Monster> input) {
    Buffer output;

    bitsery::Serializer<OutputAdapter> serializer(output);

    serializer.container(input, 100000000);
    serializer.adapter().flush();

    return output;
}

std::vector<BenchmarkTypes::Monster> bitsery_general::deserialize(std::vector<std::byte> const &input) {
    std::vector<BenchmarkTypes::Monster> output;

    bitsery::Deserializer<InputAdapter> deserializer(input.begin(), input.size());
    deserializer.container(output, 100000000);

    return output;
}
