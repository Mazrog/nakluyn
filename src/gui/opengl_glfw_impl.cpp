//
// Created by Maxime.Cabanal-Duvil on 10/30/2019.
//

#include <nakluyn/gui/opengl_glfw_impl.h>
#include <GLFW/glfw3.h>

namespace {
    GLFWmousebuttonfun g_user_mousebtn_fn = nullptr;
}

namespace nak::gui::impl {

static void mouse_events(GLFWwindow *, int, int, int) {

}


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

glfw_context::glfw_context(nak::window *window) : window(window) {
}

gui_context_impl::gui_context_impl(nak::window *window) : glfw_context(window) {

}

void gui_context_impl::setup_mouse_events() {

}


void gui_context_impl::update_mouse() {
    nak::gui::io & io = get_context()->io;
    GLFWwindow * window = glfw_context.window->glfw_window;

    if (glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        io.mouse_pos = glm::vec2(x, y);
    }
}

void gui_context_impl::glfw_new_frame() {
    update_mouse();

}

void render_ngdraw_data(draw_data const& ) {
//    for (draw_list const& drawlist : draw_data.draw_lists) {}
}

}