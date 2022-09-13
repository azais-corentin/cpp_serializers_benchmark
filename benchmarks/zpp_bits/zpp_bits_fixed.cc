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

#include "zpp_bits_fixed.hh"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4189)
#endif
#include "zpp_bits.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <cassert>
#include <iostream>

namespace BenchmarkTypes {

constexpr auto serialize(auto &archive, Vec3 &vec) { return archive(zpp::bits::as_bytes(vec)); }
constexpr auto serialize(auto &archive, Vec3 const &vec) { return archive(zpp::bits::as_bytes(vec)); }

} // namespace BenchmarkTypes

std::span<std::byte> zpp_bits_fixed::serialize(std::span<const BenchmarkTypes::Monster> input) {
    zpp::bits::out out{data_};

    if (zpp::bits::success(out(input))) { return data_; }

    return {};
}

std::span<BenchmarkTypes::Monster> zpp_bits_fixed::deserialize(std::span<const std::byte> input) {
    zpp::bits::in in{input};

    if (zpp::bits::success(in(output_))) { return output_; }

    return {};
}

/*
class ZppBitsFixedArchiver : public ISerializerTest {
  public:
    Buf serialize(const std::vector<MyTypes::Monster> &data) override {
        zpp::bits::out out{m_data};
        (void)out(data);
        return {std::data(m_data), out.position()};
    }

    void deserialize(Buf buf, std::vector<MyTypes::Monster> &resVec) override {
        (void)zpp::bits::in{std::span{buf.ptr, buf.bytesCount}}(resVec);
    }

    TestInfo testInfo() const override { return {SerializationLibrary::ZPP_BITS, "fixed buffer", ""}; }

  private:
    unsigned char m_data[150000];
};

int main() {
    ZppBitsFixedArchiver test;
    return runTest(test);
}
*/
