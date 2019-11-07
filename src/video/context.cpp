//
// Created by mazrog on 01/05/19.
//
#include "nakluyn/logger/logger.hpp"
#include <GLFW/glfw3.h>

#include "nakluyn/video/context.hpp"

namespace nak {

static void glfw_error_callback(int error, char const * message) {
    log::log(log::level::_ERROR, "GLFW error[{}]: {}", error, message);
}

/* static */
std::unique_ptr<gui::context> context::s_gui_context = nullptr;

context::context() {
    using namespace log;

    log::log(level::INFO, "Initializing GLFW...");
    if ( !glfwInit() ) {
        log::log(level::CRITICAL, "GLFW INIT ERROR : window::window");
        std::exit(ErrorStatus::GLFW_WINDOW_ERROR);
    }

     glfwSetErrorCallback(glfw_error_callback);

    /* Making a dummy window to active glfw context in order to init glew */
    GLFWwindow * hidden_window = glfwCreateWindow(1, 1, "", nullptr, nullptr);
    if ( !hidden_window ) {
        log::log(level::CRITICAL, "Hidden window creation error");
        std::exit(ErrorStatus::GLFW_WINDOW_ERROR);
    }

    glfwMakeContextCurrent(hidden_window);

    /* ########################################################## */
    // ############# GLEW PART
    glewExperimental = true;

    if (glewInit() != GLEW_OK) {
        log::log(level::CRITICAL, "GLEW initialisation error: window::window -> glewInit");
        std::exit(ErrorStatus::GLFW_WINDOW_ERROR);
    }
    glGetError();
    log::log(level::INFO, "GLEW initialized");
    /* ########################################################## */

    glfwMakeContextCurrent(nullptr);
    glfwDestroyWindow(hidden_window);
}

context::context(nak::gui::init_gui_t) : context() {
    s_gui_context = std::make_unique<gui::context>();
    log::log(log::level::INFO, "nakgui: GUI Context created");
}

context::~context() {
    glfwTerminate();
    log::log(log::level::INFO, "GLFW terminated");

    if (s_gui_context) {
        s_gui_context.reset();
        log::log(log::level::INFO, "nakgui: GUI Context destroyed");
    }
}

}