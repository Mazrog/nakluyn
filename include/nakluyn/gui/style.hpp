//
// Created by mazrog on 23/05/19.
//

#ifndef NAKLUYN_STRUCTS_HPP
#define NAKLUYN_STRUCTS_HPP

#include <glm/vec2.hpp>
#include <nakluyn/gui/font.hpp>

namespace nak::gui {

/* Font stuff */
template < id > struct font_size_t {};
template < id N > constexpr font_size_t font_size = font_size_t<N>{};

template < id > struct font_t {};
template < id Font > constexpr font_t font = font_t<Font>{};

/* ---------------------------------------------------------- */
/* Padding */
template < id T, id L, id B, id R >
struct padding_t { static constexpr std::array value = { T, L, B, R }; };

template < id T, id LR, id B >
struct padding_t<T, LR, B, mdefault> { static constexpr std::array value = { T, LR, B, LR }; };

template < id T, id L >
struct padding_t<T, L, mdefault, mdefault> { static constexpr std::array value = { T, L, T, L }; };

template < id T >
struct padding_t<T, mdefault, mdefault, mdefault> { static constexpr std::array value = { T, T, T, T }; };

template < id T, id L = mdefault, id B = mdefault, id R = mdefault >
constexpr padding_t padding = padding_t<T, L, B, R>{};



struct style {
    style() { fontsize = 12; padding = { 3, 5, 3, 5 }; }

    template < typename ... Styles >
    style(Styles &&... styles) : style() {
        (build(std::forward<Styles>(styles)), ...);
    }

    template < id N >
    void build(font_size_t<N>) { fontsize = N; }

    template < id T, id L, id B, id R >
    void build(padding_t<T, L, B, R>) { padding = padding_t<T, L, B, R>::value; }

    id fontsize;
    std::array<id, 4> padding;
};


}

#endif //NAKLUYN_STRUCTS_HPP
