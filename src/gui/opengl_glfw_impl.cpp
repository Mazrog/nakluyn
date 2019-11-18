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

    data_buffer = create_buffer();
    bind_buffer(data_buffer, GL_ARRAY_BUFFER);
    format_buffer_index_data(0, 4, GL_FLOAT, 0, (void *) 0);

    unif_texture = create_uniform(gui_prog, "gui_texture");
    unif_extracolor = create_uniform(gui_prog, "extra_color");
    send_uniform(unif_texture, texture_slot);

    font_texture = create_texture();
    bind_texture_slot(font_texture, GL_TEXTURE_2D, texture_slot);
}

gl_context::~gl_context() {
    using namespace endora::ecs;
    destroy_buffer(data_buffer);
    destroy_texture(font_texture);
    destroy_program(gui_prog);
}

/* Setting up GLFW ccontext */
glfw_context::glfw_context(nak::window *window) : window(window) {}

glm::vec2 glfw_context::apply_window_scale(glm::vec2 size) {
    glm::vec2 const window_size = glm::vec2(
            window->win_options.width,
            window->win_options.height
    );

    return size / window_size;
}

glm::vec2 glfw_context::compute_window_pos(glm::vec2 pos) {
    glm::vec2 const ogl_pos = apply_window_scale(pos) * 2.f;
    return { ogl_pos.x - 1.f, 1.f - ogl_pos.y };
}

/* Setting up the gui context custom implementation */
gui_context_impl::gui_context_impl(nak::window *window) : glfw_context(window) {}

void gui_context_impl::new_frame() {}

void gui_context_impl::render_ngdraw_data(draw_data const& data) {
    using namespace endora::ecs;

    vertex_array_t vao = create_vertexarray();
    bind_vertex_array(vao);

    for (auto const& list : data.lists) {
        std::size_t index = 0;

        bind_buffer(gl_context.data_buffer, GL_ARRAY_BUFFER);
        set_buffer_data(GL_ARRAY_BUFFER, list.buffer.size(), list.buffer.data(), GL_STATIC_DRAW);

        for (auto const& element : list.elements) {
            glm::vec2 const scale = glfw_context.apply_window_scale(element.block.size);
            glm::vec4 const vertex = glm::vec4(
                    glfw_context.compute_window_pos({element.block.vertex.x, element.block.vertex.y}),
                    glm::vec2(element.block.vertex.z, element.block.vertex.w)
            );

            glScissor(element.clip_rect.x, element.clip_rect.y, element.clip_rect.z, element.clip_rect.w);
            glDrawArrays(GL_TRIANGLE_STRIP, index, 4);
        }
    }

    destroy_vertex_array(vao);
}

}