//
// Created by mazrog on 01/05/19.
//
#include "nakluyn/logger/logger.hpp"
#include <GLFW/glfw3.h>

#include "nakluyn/video/context.hpp"
#include "nakluyn/video/registry.hpp"

namespace nak {

static void glfw_error_callback(int error, char const * message) {
    log::log(log::level::ERROR, "GLFW error[{}]: {}", error, message);
}

context::context() {
    using namespace log;

    log::log(level::INFO, "Initializing GLFW...");
    if ( !glfwInit() ) {
        log::log(level::CRITICAL, "GLFW INIT ERROR : window::window");
        std::exit(ErrorStatus::GLFW_WINDOW_ERROR);
    }

     glfwSetErrorCallback(glfw_error_callback);

    _hidden_window = glfwCreateWindow(1, 1, "", nullptr, nullptr);
    if ( !_hidden_window ) {
        log::log(level::CRITICAL, "Hidden window creation error");
        std::exit(ErrorStatus::GLFW_WINDOW_ERROR);
    }

    glfwMakeContextCurrent(_hidden_window);

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
    glfwDestroyWindow(_hidden_window);
}

context::~context() {
    registry::instance().clear();
    glfwTerminate();
    log::log(log::level::INFO, "GLFW terminated");
}

}