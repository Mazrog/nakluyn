//
// Created by mazrog on 10/11/2019.
//

#include <nakluyn/controller/io.h>
#include <nakluyn/video/window.hpp>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace {
    nak::controller::mouse_view g_mouse;
    nak::controller::keyboard_view g_keyboard;
}

static void nak_mousemove_cb(GLFWwindow * window, double x, double y) {
    if (glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
        g_mouse.mouse_pos = glm::vec2(x, y);
    }
}

static void nak_mousebutton_cb(GLFWwindow * win, int button, int action, int) {
    using namespace nak::controller;

    if (action == GLFW_PRESS)
        g_mouse.mouse_down[button] = true;

    double x, y;
    glfwGetCursorPos(win, &x, &y);
    g_mouse.mouse_pos = glm::vec2(x, y);

    g_keyboard.keyboard_modifiers[KBModifiers::CTRL] = g_keyboard.key_down[GLFW_KEY_LEFT_CONTROL] || g_keyboard.key_down[GLFW_KEY_RIGHT_CONTROL];
    g_keyboard.keyboard_modifiers[KBModifiers::SHIFT] = g_keyboard.key_down[GLFW_KEY_LEFT_SHIFT] || g_keyboard.key_down[GLFW_KEY_RIGHT_SHIFT];
    g_keyboard.keyboard_modifiers[KBModifiers::ALT] = g_keyboard.key_down[GLFW_KEY_LEFT_ALT] || g_keyboard.key_down[GLFW_KEY_RIGHT_ALT];
}

static void nak_key_cb(GLFWwindow *, int key, int, int action, int) {
    if (action == GLFW_PRESS)
        g_keyboard.key_down[key] = true;
    if (action == GLFW_RELEASE)
        g_keyboard.key_down[key] = false;
}

static void nak_char_cb(GLFWwindow *, unsigned codepoint) {
    g_keyboard.push_char(static_cast<char>(codepoint));
}

namespace nak::controller {

io::io(nak::window const& win) : want_capture_mouse(false), want_capture_keyboard(false), window(win) {
    glfwSetMouseButtonCallback(window.glfw_window, nak_mousebutton_cb);
    glfwSetCursorPosCallback(window.glfw_window, nak_mousemove_cb);
    glfwSetKeyCallback(window.glfw_window, nak_key_cb);
    glfwSetCharCallback(window.glfw_window, nak_char_cb);
}

mouse_view const& io::mouse() {
    return g_mouse;
}

keyboard_view const& io::keyboard() {
    return g_keyboard;
}

}