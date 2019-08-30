//
// Created by mazrog on 29/04/19.
//
#include "nakluyn/logger/logger.hpp"
#include "nakluyn/nakluyn.hpp"
#include "nakluyn/gui/gui_window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

        if (window->gui_window) {
            window->gui_window->render();
        }

        glfwSwapBuffers(window->glfw_window);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    window->gui_window->close();
}

window::window(nak::window_options options)
    : win_options(std::move(options)),
    parent(nullptr),
    gui_window(nullptr)
{
    using namespace nak::log;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, win_options.opengl_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, win_options.opengl_version_minor);
    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
    glfwWindowHint(GLFW_DECORATED, win_options.decorated);
    glfwWindowHint(GLFW_DEPTH_BITS, win_options.depth_bits);    // 24 default value but still explicit


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
}

window::~window() {
    glfwDestroyWindow(glfw_window);
    log::log(log::level::INFO, "Window \"{}\" destroyed.", win_options.title);
}

bool window::should_close() const {
    return glfwWindowShouldClose(glfw_window);
}

void window::should_close(bool should_close) {
    glfwSetWindowShouldClose(glfw_window, should_close);
}

void window::swap() const {
    glfwSwapBuffers(glfw_window);
}

void window::poll_events() const {
    glfwPollEvents();
}

}