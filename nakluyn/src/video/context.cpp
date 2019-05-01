//
// Created by mazrog on 01/05/19.
//

#include <GLFW/glfw3.h>

#include "nakluyn/video/context.hpp"
#include "nakluyn/logger/logger.hpp"
#include "nakluyn/video/registry.hpp"

namespace nak {

context::context() {
    using namespace log;

    log::log(level::INFO, "Initializing GLFW...");
    if ( !glfwInit() ) {
        log::log(level::CRITICAL, "GLFW INIT ERROR : window::window");
        std::exit(ErrorStatus::GLFW_WINDOW_ERROR);
    }

    // glfwSetErrorCallback(glfw_error_callback);
}

context::~context() {
    registry::instance().clear();
    glfwTerminate();
    log::log(log::level::INFO, "GLFW terminated");
}

void context::glew_init() const {
    static bool glew_has_init = false;

    using namespace log;
    if (!glew_has_init) {
        glewExperimental = true;

        if (glewInit() != GLEW_OK) {
            log::log(level::CRITICAL, "GLEW initialisation error: window::window -> glewInit");
            std::exit(ErrorStatus::GLFW_WINDOW_ERROR);
        }
        glGetError();
        log::log(level::INFO, "GLEW initialized");
        glew_has_init = true;
    }
}

}