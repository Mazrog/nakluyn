//
// Created by mazrog on 13/05/19.
//

#ifndef NAKLUYN_RENDERER_HPP
#define NAKLUYN_RENDERER_HPP

#include <array>
#include <extern/endora.hpp>

namespace {
    using _nakgui_unif_block = endora::utils::types_wrapper<glm::vec2, glm::vec2, glm::vec3>;
}

UnifBlock(NakGuiVertBlock, ::_nakgui_unif_block, position, scale, color)

namespace nak::gui {

struct UnifBlock {
    enum blocks {
        GUIVERT,

        COUNT
    };
};

}

#endif //NAKLUYN_RENDERER_HPP
