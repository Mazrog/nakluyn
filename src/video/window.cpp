//
// Created by mazrog on 29/04/19.
//
#include <nakluyn/logger/logger.hpp>
#include <nakluyn/nakluyn.hpp>
#include <nakluyn/gui/opengl_glfw_impl.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace nak {

void window_loop(window * window, gui::render_fn gui_callback) {
    while (!glfwWindowShouldClose(window->glfw_window)) {
        glfwPollEvents();

        gui_callback();

        int display_w, display_h;
        glfwGetFramebufferSize(window->glfw_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(.3, .3, .3, 1.);
        glClear(GL_COLOR_BUFFER_BIT);

        gui::render_ngdraw_data(gui::get_draw_data());

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        glfwSwapBuffers(window->glfw_window);
    }
}

window::window(nak::window_options options)
    : win_options(std::move(options))
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