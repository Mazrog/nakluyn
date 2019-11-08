//
// Created by Maxime.Cabanal-Duvil on 10/30/2019.
//

#include <nakluyn/gui/opengl_glfw_impl.h>
#include <GLFW/glfw3.h>
#include <array>

namespace {
    std::array<bool, nak::controller::MouseButton::MB_COUNT>    g_mouse_just_pressed;
}

namespace nak::gui::impl {

static void mouse_cb(GLFWwindow *, int button, int action, int) {
    if (action == GLFW_PRESS && button >= 0 && button < g_mouse_just_pressed.size())
        g_mouse_just_pressed[button] = true;
}

static void key_cb(GLFWwindow *, int key, int, int action, int) {
    using namespace nak::controller;

    io & io = get_io();
    if (action == GLFW_PRESS) {
        io.key_down[key] = true;
    }
    if (action == GLFW_RELEASE) {
        io.key_down[key] = false;
    }

    io.keyboard_modifiers[KBModifiers::CTRL] = io.key_down[GLFW_KEY_LEFT_CONTROL] || io.key_down[GLFW_KEY_RIGHT_CONTROL];
    io.keyboard_modifiers[KBModifiers::SHIFT] = io.key_down[GLFW_KEY_LEFT_SHIFT] || io.key_down[GLFW_KEY_RIGHT_SHIFT];
    io.keyboard_modifiers[KBModifiers::ALT] = io.key_down[GLFW_KEY_LEFT_ALT] || io.key_down[GLFW_KEY_RIGHT_ALT];
}

static void char_cb(GLFWwindow*, unsigned int c) {
    controller::io & io = get_io();
    io.push_char(static_cast<char>(c));
}

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
glfw_context::glfw_context(nak::window *window) : window(window) {
    glfwSetMouseButtonCallback(window->glfw_window, mouse_cb);
    glfwSetKeyCallback(window->glfw_window, key_cb);
    glfwSetCharCallback(window->glfw_window, char_cb);
}

/* Setting up the gui context custom implementation */
gui_context_impl::gui_context_impl(nak::window *window) : glfw_context(window) {}


void gui_context_impl::setup_mouse_events() {}

void gui_context_impl::setup_keyboard_events() {}

void gui_context_impl::update_mouse() {
    nak::controller::io & io = get_context()->io;
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