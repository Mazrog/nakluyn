//
// Created by mazrog on 13/05/19.
//

#include <endora/program.hpp>
#include <endora/structs/vao.hpp>
#include <nakluyn/gui/gui_window.hpp>

namespace nak::gui {

struct gui_render_context {
    gui_render_context() {
        static ShaderProgram    s_guiprog{
            Shader{ "nakluyn/include/nakluyn/shaders/gui.vert", GL_VERTEX_SHADER },
            Shader{ "nakluyn/include/nakluyn/shaders/gui.frag", GL_FRAGMENT_SHADER }
            };
        static Vao  s_vao;

        s_guiprog.use();
        s_vao.bind();
    }

    ~gui_render_context() {
        ShaderProgram::use(0);
        Vao::bind_vao(0);
    }
};

guiwindow::guiwindow(nak::window_t window) : window(window) {}

void guiwindow::close() {
    window->should_close(true);
}

void guiwindow::minimize() {}

basewindow::basewindow(window_t window) : guiwindow(window) {}

void basewindow::render() {
    gui_render_context guictx;
    paint(this, bar);
}

}