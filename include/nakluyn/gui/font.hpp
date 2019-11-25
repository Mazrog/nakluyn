//
// Created by Maxime.Cabanal-Duvil on 11/21/2019.
//

#ifndef NAKLUYN_FONT_HPP
#define NAKLUYN_FONT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H

namespace nak::gui {

using id = unsigned short;
constexpr id mdefault = -1;

struct font_atlas {
    id register_font(FT_Face font) {
        fonts.push_back(font);
        return static_cast<id>(fonts.size() - 1);
    }

    void push_font(id font_id) {
        assert(font_id < fonts.size());
        current_font = font_id;
    }

    void pop_font() {
        current_font = 0;
    }

    operator FT_Face () {
        return fonts[current_font];
    }

    id current_font = 0;
    std::vector<FT_Face> fonts;
};

}

#endif //NAKLUYN_FONT_HPP
