//
// Created by Maxime.Cabanal-Duvil on 10/30/2019.
//

#include <nakluyn/gui/opengl_glfw_impl.h>

namespace nak::gui::impl {

/* Setting up OpenGL context */
gl_context::gl_context() {
    using namespace endora::ecs;

    gui_prog = create_program(
            create_shader(GL_VERTEX_SHADER, "include/nakluyn/shaders/gui.vert"),
            create_shader(GL_FRAGMENT_SHADER, "include/nakluyn/shaders/gui.frag")
    );
    create_buffers(buffers, BUFFERCOUNT);
    unif_shape = create_uniform(gui_prog, "shape");
    unif_texture = create_uniform(gui_prog, "gui_texture");

    use_program(gui_prog);

    glm::vec4 color(.3, .4, .6, 1.);
    gui_vert_block.set(ubo::NakGuiVertBlock::fields::color, glm::value_ptr(color));
}

gl_context::~gl_context() {
    using namespace endora::ecs;
    destroy_buffers(buffers, BUFFERCOUNT);
    destroy_program(gui_prog);
}

/* Setting up GLFW ccontext */
glfw_context::glfw_context(nak::window *window) : window(window) {}

/* Setting up the gui context custom implementation */
gui_context_impl::gui_context_impl(nak::window *window) : glfw_context(window) {}


void gui_context_impl::new_frame() {}

void gui_context_impl::render_ngdraw_data(draw_data const& ) {
    using namespace endora::ecs;

    glm::vec2 pos (0, 0),
        size(120 / 600., 120 / 400.);

    gl_context.gui_vert_block.set(
            ubo::NakGuiVertBlock::fields::position,
            glm::value_ptr(pos)
            );

    gl_context.gui_vert_block.set(
            ubo::NakGuiVertBlock::fields::scale,
            glm::value_ptr(size)
    );

    vertex_array_t vao = create_vertexarray();
    bind_vertex_array(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    destroy_vertex_array(vao);
}

}