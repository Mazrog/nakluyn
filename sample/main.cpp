#include <iostream>

#include <nakluyn/nakluyn.hpp>
#include <nakluyn/controller/controller.hpp>

enum class MainState {
    IDLE
};

MainState idle_action(nak::controller::event_detail const& detail, nak::window_t win) {
    if (detail.key.action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(win->glfw_window, &x, &y);
        std::cout << "Cursor at " << x << ", " << y << '\n';
        nak::controller::event_detail evdetail(detail);
        evdetail.position = {x, y};
    }
    return MainState::IDLE;
}

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

    nak::window_t window = nak::make_window(options, nullptr);

    {
        using namespace nak::controller;
        using EvCtx = event_context<
                MainState,
                MainState (*) (event_detail const&, nak::window_t)
                >;

        EvCtx ev_ctx;
        ev_ctx.setup(MainState::IDLE, idle_action, MainState::IDLE);
        ev_ctx.set_context(window);

        // phase de branchement
        // brancher la récéption d'input sur des méthodes de event_context
        sub_keyboard(window, &ev_ctx);


        nak::window_loop(window, render_gui);
    }

    return 0;
}

