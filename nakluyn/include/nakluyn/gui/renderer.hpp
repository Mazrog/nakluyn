//
// Created by mazrog on 13/05/19.
//

#ifndef NAKLUYN_RENDERER_HPP
#define NAKLUYN_RENDERER_HPP

#include <array>
#include <endora/structs/uniform_block.hpp>

namespace {
    using _nakgui_unif_block = types_wrapper<glm::vec2, glm::vec2, glm::vec3>;
}

namespace nak::gui {

struct UnifBlock {
    enum blocks {
        GUIVERT,

        COUNT
    };
};

UnifBlock(NakGuiVertBlock, _nakgui_unif_block, position, scale, color)

}

#endif //NAKLUYN_RENDERER_HPP
