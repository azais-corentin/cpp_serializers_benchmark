#pragma once

#include "common/types.h"

#include <cstddef>
#include <span>
#include <vector>

// Those definitions absolutely need to be in a header file (or specialized and in a source file)
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

struct bitsery_general {
    std::vector<std::byte> serialize(std::vector<BenchmarkTypes::Monster> input);

    std::vector<BenchmarkTypes::Monster> deserialize(std::vector<std::byte> const &input);

  private:
    // std::vector<std::byte> buffer_;
};
