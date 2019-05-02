//
// Created by mazrog on 29/04/19.
//
#include "nakluyn/logger/logger.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "nakluyn/nakluyn.hpp"

namespace nak {

window_t make_window(window_options const& options, window_t parent) {
    auto new_window = std::make_shared<window>(options);
    new_window->parent = parent;
    if (parent) {
        parent->children.push_back(new_window.get());
    }
    registry::instance().register_window(new_window);
    return new_window.get();
}

void window_loop(window_t window) {
    while (!glfwWindowShouldClose(window->glfw_window)) {
        glfwPollEvents();



        glfwSwapBuffers(window->glfw_window);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

window::window(nak::window_options options)
    : win_options(std::move(options)),
    parent(nullptr)
{
    using namespace nak::log;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);


    glfw_window = glfwCreateWindow(
            win_options.width,
            win_options.height,
            win_options.title.c_str(),
            nullptr,
            nullptr
    );
    log::log(level::INFO, "Creating window \"{}\", size {}x{}", win_options.title, win_options.width, win_options.height);

    if ( !glfw_window ) {
        log::log(level::CRITICAL, "Window creation error: window {}", win_options.title);
        std::exit(ErrorStatus::GLFW_WINDOW_ERROR);
    }

    glfwMakeContextCurrent(glfw_window);

    glfwSwapInterval(1);
    apply_flags();
}

window::~window() {
    glfwDestroyWindow(glfw_window);
    log::log(log::level::INFO, "Window \"{}\" destroyed.", win_options.title);
}

void window::apply_flags() {
    using namespace log;

    log::log(level::INFO, "Window options:");
    if (win_options.flags & window_flags::BLEND) {
        glEnable(GL_BLEND);
        gl_error("window::window -> Enabling blending function");
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        gl_error("window::window -> Setting the blend function");
        log::log(level::INFO, "\tBlend enabled");
    }
    if (win_options.flags & window_flags::DEPTH) {
        glEnable(GL_DEPTH_TEST);
        gl_error("window::window -> Enabling depth test");
        log::log(level::INFO, "\tDepth test enabled");
    }
}

}