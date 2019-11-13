#ifndef NAKLUYN_HPP
#define NAKLUYN_HPP

#include <nakluyn/video/context.hpp>
#include <nakluyn/video/window.hpp>
#include <nakluyn/gui/gui.hpp>

#include <nakluyn/gui/opengl_glfw_impl.h>

#include <thread>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace nak {

template < typename Impl >
void window_loop(window * window,
        void (*gui_render_func)(),
        Impl & impl
        ) {
    while (!glfwWindowShouldClose(window->glfw_window)) {
        glfwPollEvents();

        impl.new_frame();
        gui::new_frame();

        gui_render_func();

        int display_w, display_h;
        glfwGetFramebufferSize(window->glfw_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(.3, .3, .3, 1.);
        glClear(GL_COLOR_BUFFER_BIT);

        impl.render_ngdraw_data(gui::get_draw_data());

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        glfwSwapBuffers(window->glfw_window);
    }
}

}

#endif