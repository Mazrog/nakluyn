#include <iostream>
#include "nakluyn/nakluyn.hpp"

int main() {
    nak::context context;

    nak::window_options options;
    options.title = "Nakluyn sample";
    options.width = 1600;
    options.height = 900;
    options.flags = nak::window_flags::DEPTH | nak::window_flags::BLEND;
    options.opengl_version_major = 4; options.opengl_version_minor = 5;
    options.depth_bits = 24;

    nak::window_t window = nak::make_window(options, nullptr);


    nak::window_loop(window);

    return 0;
}

