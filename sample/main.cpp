#include <iostream>
#include <chrono>
#include <thread>
#include "nakluyn/nakluyn.hpp"

int main() {
    nak::context context;

    nak::window_options options;
    options.title = "Nakluyn sample";
    options.width = 1600;
    options.height = 900;
    options.flags = nak::window_flags::DEPTH | nak::window_flags::BLEND;

    nak::window_t window = nak::make_window(options);


    nak::window_loop(window);

    return 0;
}

