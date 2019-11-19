#include <nakluyn/nakluyn.hpp>
#include <nakluyn/gui/opengl_glfw_impl.hpp>

void render_gui() {
    namespace ng = nak::gui;
    if (ng::begin(0)) {
        if (ng::button("Click me")) {
            std::cout << "Button clicked!\n";
        }

        ng::end();
    }
}

int main() {
    nak::context context(nak::gui::init_gui);

    nak::window_options options{
            "Nakluyn sample",
            600,
            400,
            24,
            4, 5,
            true
    };

    nak::window window(options);
    nak::controller::io io(window);

    nak::gui::set_io(&io);
    nak::gui::set_window_context(&window);

    nak::gui::gui_context_impl impl(&window);

    nak::window_loop(&window, render_gui, impl);

    return 0;
}

