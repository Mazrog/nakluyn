//
// Created by mazrog on 23/05/19.
//

#ifndef NAKLUYN_STRUCTS_HPP
#define NAKLUYN_STRUCTS_HPP

#include <glm/vec2.hpp>
#include <nakluyn/gui/font.hpp>

namespace nak::gui {

using macro = unsigned short;
constexpr macro mdefault = -1;

/* Font stuff */
template < macro N >
struct font_size_t {};

template < macro N >
constexpr font_size_t font_size = font_size_t<N>{};

/* Padding */
template < macro T, macro L, macro B, macro R >
struct padding_t { static constexpr std::array value = { T, L, B, R }; };

template < macro T, macro LR, macro B >
struct padding_t<T, LR, B, mdefault> { static constexpr std::array value = { T, LR, B, LR }; };

template < macro T, macro L >
struct padding_t<T, L, mdefault, mdefault> { static constexpr std::array value = { T, L, T, L }; };

template < macro T >
struct padding_t<T, mdefault, mdefault, mdefault> { static constexpr std::array value = { T, T, T, T }; };

template < macro T, macro L = mdefault, macro B = mdefault, macro R = mdefault >
constexpr padding_t padding = padding_t<T, L, B, R>{};



template < typename ... Ts >
struct style {
    style() { fontsize = 12; padding = { 3, 5, 3, 5 }; }
    style(Ts ... styles) : style() { (build(styles), ...); }

    template < macro N >
    void build(font_size_t<N>) { fontsize = N; }

    template < macro T, macro L, macro B, macro R >
    void build(padding_t<T, L, B, R>) { padding = padding_t<T, L, B, R>::value; }

    macro fontsize;
    std::array<macro, 4> padding;
};


}

#endif //NAKLUYN_STRUCTS_HPP
