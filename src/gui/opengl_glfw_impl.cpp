//
// Created by Maxime.Cabanal-Duvil on 10/30/2019.
//

#include <nakluyn/gui/opengl_glfw_impl.hpp>
#include <nakluyn/video/window.hpp>

namespace nak::gui::impl {

/* Setting up OpenGL context */
gl_context::gl_context() {
    using namespace endora::ecs;

    gui_prog = create_program(
            create_shader(GL_VERTEX_SHADER, "include/nakluyn/shaders/gui.vert"),
            create_shader(GL_FRAGMENT_SHADER, "include/nakluyn/shaders/gui.frag")
    );
    use_program(gui_prog);

    vertex_array = create_vertexarray();
    bind_vertex_array(vertex_array);

    data_buffer = create_buffer();
    bind_buffer(data_buffer, GL_ARRAY_BUFFER);
    format_buffer_index_data(0, 4, GL_FLOAT, 0, nullptr);

    unif_texture = create_uniform(gui_prog, "gui_texture");
    unif_extracolor = create_uniform(gui_prog, "extra_color");
    send_uniform(unif_texture, texture_slot);

    font_texture = create_texture();
    bind_texture_slot(font_texture, GL_TEXTURE_2D, texture_slot);
}

gl_context::~gl_context() {
    using namespace endora::ecs;
    destroy_buffer(data_buffer);
    destroy_vertex_array(vertex_array);
    destroy_texture(font_texture);
    destroy_program(gui_prog);
}

/* Setting up GLFW ccontext */
glfw_context::glfw_context(nak::window *window) : window(window) {}

/* Setting up the gui context custom implementation */
gui_context_impl::gui_context_impl(nak::window *window) : glfw_context(window) {}

void gui_context_impl::new_frame() {}

void render_quad(gl_context & glctx, base_draw_unit const& base_unit) {
    endora::ecs::send_uniform(glctx.unif_extracolor, base_unit.color);

    glScissor(base_unit.clip_rect.x, base_unit.clip_rect.y, base_unit.clip_rect.z, base_unit.clip_rect.w);
    glDrawArrays(GL_TRIANGLE_STRIP, base_unit.buffer_index, 4);
}

void render_text(gl_context & , text_draw_unit const ) { puts("Text render"); }

void gui_context_impl::render_ngdraw_data(draw_data const& data) {
    using namespace endora::ecs;

    for (auto const& list : data.lists) {
        bind_buffer(gl_context.data_buffer, GL_ARRAY_BUFFER);
        set_buffer_data(GL_ARRAY_BUFFER, list.buffer.size() * sizeof(gui::vertex), list.buffer.data(), GL_STATIC_DRAW);

        for (auto const& unit : list.units) {
            std::visit(utils::overloaded {
                [this] (base_draw_unit const& base_unit) { render_quad(gl_context, base_unit); },
                [this] (text_draw_unit const& text_unit) { render_text(gl_context, text_unit); },
                },
                        unit);
        }
    }
}

}