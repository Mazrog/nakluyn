//
// Created by Maxime.Cabanal-Duvil on 10/30/2019.
//

#ifndef NAKLUYN_OPENGL_GLFW_IMPL_H
#define NAKLUYN_OPENGL_GLFW_IMPL_H

#include <extern/endora.hpp>
#include <nakluyn/gui/gui.hpp>

namespace {
    using _nakgui_unif_block = endora::utils::types_wrapper<int, glm::vec2, glm::vec2, glm::vec4>;
}

namespace nak::gui {

inline namespace impl {
UnifBlock(NakGuiVertBlock, ::_nakgui_unif_block, shape, position, scale, color)

enum UnifBlock { GUIVERT, COUNT };

struct gl_context {
    enum Buffers { DATABUFFER, ELEMENTBUFFER, BUFFERCOUNT };
    endora::ecs::program_t gui_prog;
    endora::ecs::buffer_t buffers[BUFFERCOUNT];

    endora::ecs::texture_t font_texture;
    endora::ecs::uniform_t unif_texture;
    endora::ecs::UniformBlock<ubo::NakGuiVertBlock>    gui_vert_block{UnifBlock::GUIVERT};

    gl_context();
    ~gl_context();
};

struct glfw_context {
    nak::window * window;

    glfw_context(nak::window * window);
    glm::vec2 apply_window_scale(glm::vec2 size);
    glm::vec2 compute_window_pos(glm::vec2 pos);
};

struct gui_context_impl {
    impl::gl_context      gl_context;
    impl::glfw_context    glfw_context;

    explicit gui_context_impl(nak::window * window);

    void new_frame();

    void render_ngdraw_data(draw_data const& draw_data);
};

}

}

#endif //NAKLUYN_OPENGL_GLFW_IMPL_H
