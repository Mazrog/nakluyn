#include <iostream>

#include "nakluyn/nakluyn.hpp"
#include "nakluyn/controller/controller.hpp"
#include "nakluyn/gui/gui_window.hpp"

enum class MainState {
    IDLE
};

MainState idle_action(nak::controller::event_detail const& detail) {
    std::cout << detail.key.key << " -- " << (detail.key.action == GLFW_PRESS ? "pressed" : "released") << "\n";
    return MainState::IDLE;
}

int main() {
    nak::context context;

    nak::window_options options;
    options.title = "Nakluyn sample";
    options.width = 1600;
    options.height = 900;
    options.opengl_version_major = 4; options.opengl_version_minor = 5;
    options.depth_bits = 24;
    options.decorated = false;

    nak::window_t window = nak::make_window(options, nullptr);

    nak::gui::setup_gui<nak::gui::basewindow>(window);

    {
        using namespace nak::controller;
        using EvCtx = event_context<
                MainState,
                MainState (*) (event_detail const&)
                >;

        EvCtx ev_ctx;
        ev_ctx.setup(MainState::IDLE, idle_action, MainState::IDLE);

        // phase de branchement
        // brancher la récéption d'input sur des méthodes de event_context
        sub_keyboard(window, &ev_ctx);


        nak::window_loop(window);
    }

    return 0;
}

