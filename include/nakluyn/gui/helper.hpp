//
// Created by mazrog on 23/05/19.
//

#ifndef NAKLUYN_STRUCTS_HPP
#define NAKLUYN_STRUCTS_HPP

#include <glm/vec2.hpp>

namespace nak::gui {

inline namespace helpers {

inline glm::vec2 pos_from_glfw(float x, float y, glm::vec2 const& win_dim) {
    return 2.f * (glm::vec2(x, y) / win_dim);
}

}

namespace literals {

}

struct Distance {
    int value;

    operator int() const { return value; }
};

struct Color {};

struct Caret {};

}

#endif //NAKLUYN_STRUCTS_HPP
