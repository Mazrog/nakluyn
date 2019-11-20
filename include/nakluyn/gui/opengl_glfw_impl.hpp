//
// Created by Maxime.Cabanal-Duvil on 10/30/2019.
//

#ifndef NAKLUYN_OPENGL_GLFW_IMPL_H
#define NAKLUYN_OPENGL_GLFW_IMPL_H

#include <extern/endora.hpp>
#include <nakluyn/gui/gui.hpp>


namespace nak::gui {

inline namespace impl {

enum UnifBlock { GUIVERT, COUNT };
inline constexpr int texture_slot = 0;

struct gl_context {
    endora::ecs::program_t gui_prog;
    endora::ecs::vertex_array_t vertex_array;
    endora::ecs::buffer_t data_buffer;

    endora::ecs::texture_t font_texture;
    endora::ecs::uniform_t unif_texture, unif_extracolor;
    gl_context();
    ~gl_context();
};

struct gui_context_impl {
    impl::gl_context      gl_context;

    explicit gui_context_impl();

    void new_frame();
    void render_ngdraw_data(draw_data const& draw_data);
};

}

}

#endif //NAKLUYN_OPENGL_GLFW_IMPL_H
