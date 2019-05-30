//
// Created by mazrog on 23/05/19.
//

#ifndef NAKLUYN_STRUCTS_HPP
#define NAKLUYN_STRUCTS_HPP

namespace nak::gui {

namespace literals {

}

struct Distance {
    int value;

    operator int() const { return value; }
};

struct Color {};

struct Caret {

};

}

#endif //NAKLUYN_STRUCTS_HPP
