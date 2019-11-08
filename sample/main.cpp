#include <nakluyn/nakluyn.hpp>
#include <nakluyn/controller/controller.hpp>
#include <nakluyn/gui/opengl_glfw_impl.h>
#include <functional>


static void events() {}

void render_gui() {

}

int main() {
    nak::context context(nak::gui::init_gui);

    nak::window_options options;
    options.title = "Nakluyn sample";
    options.width = 600;
    options.height = 400;
    options.opengl_version_major = 4; options.opengl_version_minor = 5;
    options.depth_bits = 24;
    options.decorated = true;

    nak::window window(options);

    nak::gui::gui_context_impl impl(&window);

    nak::window_loop(&window, render_gui, std::bind(&nak::gui::gui_context_impl::glfw_new_frame, impl));

    return 0;
}

