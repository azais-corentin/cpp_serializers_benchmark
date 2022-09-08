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

std::vector<std::byte> bitsery_general::serialize(std::vector<BenchmarkTypes::Monster> input) {
    Buffer output;

    bitsery::Serializer<OutputAdapter> serializer(output);

    serializer.container(input, 10000000);
    serializer.adapter().flush();

    return output;
}

std::vector<BenchmarkTypes::Monster> bitsery_general::deserialize(const std::vector<std::byte> &input) {
    std::vector<BenchmarkTypes::Monster> output;

    bitsery::Deserializer<InputAdapter> deserializer(input.begin(), input.size());
    deserializer.container(output, 100000000);

    return output;
}

/*

class BitseryArchiver : public ISerializerTest {
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
            "general",
            ""
        };
    }

  private:
    Buffer _buf{};
};

int main() {
    BitseryArchiver test{};
    return runTest(test);
}
*/
