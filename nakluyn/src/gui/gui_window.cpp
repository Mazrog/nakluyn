//
// Created by mazrog on 13/05/19.
//
#include <GL/glew.h>
#include <nakluyn/gui/gui_window.hpp>
#include <nakluyn/controller/events.hpp>
#include <GLFW/glfw3.h>

namespace nak::gui {

guiwindow::guiwindow(nak::window_t window) : window(window) {
    glDisable(GL_DEPTH_TEST); endora_error("disable depth test");
    glDisable(GL_CULL_FACE);  endora_error("disable cull face");
    glEnable(GL_BLEND); endora_error("enable blend");
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); endora_error("blend func");
}

void guiwindow::close() {
    window->should_close(true);
}

void guiwindow::minimize() {
    glfwIconifyWindow(window->glfw_window);
}

void basewindow::render() {
    glClear(GL_COLOR_BUFFER_BIT); endora_error("clearing");
    draw(bar, this);
}

void basewindow::on(controller::event_detail const& detail) {
    puts("basewindow on");

    double x = detail.position.x,
            y = detail.position.y,
            tx = bar.position[0], ty = bar.position[1],
            tw = bar.size[0], th = bar.size[1];
    bool cond = (x >= tx) && (x <= tx + tw) && (y >= ty) && (y <= ty + th);
    if (cond) {
        return bar.on(detail);
    }
}

}