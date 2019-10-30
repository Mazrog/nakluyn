//
// Created by Maxime.Cabanal-Duvil on 10/30/2019.
//

#ifndef NAKLUYN_OPENGL_GLFW_IMPL_H
#define NAKLUYN_OPENGL_GLFW_IMPL_H

#include <extern/endora.hpp>

namespace {
    using _nakgui_unif_block = endora::utils::types_wrapper<glm::vec2, glm::vec2, glm::vec3>;
}

namespace nak::gui {
UnifBlock(NakGuiVertBlock, ::_nakgui_unif_block, position, scale, color)

enum UnifBlock { GUIVERT, COUNT };

struct glContext {
    enum Buffers { DATABUFFER, ELEMENTBUFFER, BUFFERCOUNT };
    endora::ecs::program_t gui_prog;
    endora::ecs::buffer_t buffers[BUFFERCOUNT];

    endora::ecs::texture_t font_texture;
    endora::ecs::uniform_t unif_transform, unif_texture;
    endora::ecs::UniformBlock<ubo::NakGuiVertBlock>    guiVertBlock{UnifBlock::GUIVERT};

    glContext();
    ~glContext();
};



}

#endif //NAKLUYN_OPENGL_GLFW_IMPL_H
