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

#include "bitsery_brief_syntax.hh"

#include <bitsery/adapter/buffer.h>
#include <bitsery/bitsery.h>
#include <bitsery/brief_syntax.h>
#include <bitsery/brief_syntax/string.h>
#include <bitsery/brief_syntax/vector.h>
#include <bitsery/traits/string.h>
#include <bitsery/traits/vector.h>

using Buffer        = std::vector<std::byte>;
using InputAdapter  = bitsery::InputBufferAdapter<Buffer>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;

namespace bitsery {

template <typename S> void serialize(S &s, BenchmarkTypes::Vec3 &o) { s(o.x, o.y, o.z); }
template <typename S> void serialize(S &s, BenchmarkTypes::Weapon &o) {
    s(maxSize(o.name, 10), // this maxSize function is optional
      o.damage);
}
template <typename S> void serialize(S &s, BenchmarkTypes::Monster &o) {
    s(maxSize(o.name, 10), o.equipped, maxSize(o.weapons, 10), o.pos, maxSize(o.path, 10), o.mana,
      maxSize(o.inventory, 10), o.hp, o.color);
}

} // namespace bitsery

/**
 * Bitsery traits for std::span container
 */
namespace bitsery::traits {

template <typename T> struct ContainerTraits<std::span<T>> : public StdContainer<std::span<T>, true, true> {};

template <typename T> struct BufferAdapterTraits<std::span<T>> : public StdContainerForBufferAdapter<std::span<T>> {};

} // namespace bitsery::traits

std::vector<std::byte> bitsery_brief_syntax::serialize(std::span<const BenchmarkTypes::Monster> input) {
    Buffer output;
    bitsery::Serializer<OutputAdapter> serializer(output);

    serializer.container(input, 100000000);
    serializer.adapter().flush();

    return output;
}
std::vector<BenchmarkTypes::Monster> bitsery_brief_syntax::deserialize(std::vector<std::byte> const &input) {
    std::vector<BenchmarkTypes::Monster> output;

    bitsery::Deserializer<InputAdapter> deserializer(input.begin(), input.size());
    deserializer.container(output, 100000000);

    return output;
}
/*
#include <bitsery/adapter/buffer.h>
#include <bitsery/bitsery.h>
#include <bitsery/brief_syntax.h>
#include <bitsery/brief_syntax/string.h>
#include <bitsery/brief_syntax/vector.h>
#include <testing/test.h>


namespace bitsery {



}

using Buffer = std::vector<uint8_t>;
using InputAdapter = bitsery::InputBufferAdapter<Buffer>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;

class BitseryVerboseSyntaxArchiver : public ISerializerTest {
  public:

    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        _buf.clear();
        bitsery::Serializer<OutputAdapter> ser(_buf);
        ser.container(data, 100000000);
        ser.adapter().flush();
        return Buf{std::addressof(*std::begin(_buf)), ser.adapter().writtenBytesCount()};
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &res) override {
        bitsery::Deserializer<InputAdapter> des(_buf.begin(), buf.bytesCount);
        des.container(res, 100000000);
    }

    TestInfo testInfo() const override {
        return {
            SerializationLibrary::BITSERY,
            "brief syntax",
            "deserialization using `brief_syntax`, similar to `cereal`"
        };
    }

  private:
    Buffer _buf{};
};

int main() {
    BitseryVerboseSyntaxArchiver test{};
    return runTest(test);
}
*/
