#pragma once

#include <array>
#include <exception>

namespace ricefish {

enum class Pebble {
    NO_PEBBLE = 0, P1, P2,

    // Invalid squares set to non-zero to avoid bugs.
    INVALID = 123
};

inline constexpr Pebble operator~ (Pebble pebble) {
    switch (pebble) {
        case Pebble::P1:
            return Pebble::P2;
        case  Pebble::P2:
            return Pebble::P1;
        default:
            throw std::invalid_argument("Can only negate P1 and P2");
    }
}

namespace Pebbles {

constexpr int VALUES_SIZE = 3;

constexpr std::array<Pebble, VALUES_SIZE> values = {
    Pebble::NO_PEBBLE, Pebble::P1, Pebble::P2
};

inline constexpr bool is_valid(Pebble pebble) {
    return pebble != Pebble::INVALID;
}
inline constexpr bool is_pebble(Pebble pebble) {
    return pebble == Pebble::P1 or pebble == Pebble::P2;
}

inline constexpr char get_char(Pebble pebble) {
    switch (pebble) {
        case Pebble::NO_PEBBLE:
            return '.';
        case Pebble::P1:
            return 'x';
        case Pebble::P2:
            return '+';
        default:
            return ' ';
    }
}


}
}
