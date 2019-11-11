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
    unif_transform = create_uniform(gui_prog, "transform");
    unif_texture = create_uniform(gui_prog, "gui_texture");

    use_program(gui_prog);
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


void gui_context_impl::setup_mouse_events() {}

void gui_context_impl::setup_keyboard_events() {}


void gui_context_impl::glfw_new_frame() {}

void render_ngdraw_data(draw_data const& ) {
//    for (draw_list const& drawlist : draw_data.draw_lists) {}
}

}