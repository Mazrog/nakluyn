//
// Created by mazrog on 28/04/19.
//

#ifndef NAKLUYN_WINDOW_HPP
#define NAKLUYN_WINDOW_HPP

#include <string>

struct GLFWwindow;

namespace nak {

using flag_t = uint64_t;

enum window_flags : flag_t {
    NONE,
    DEPTH       = 0x01,
    BLEND       = 0x02
};

struct window_options {
    std::string title;
    int width;
    int height;
    flag_t flags;
};

struct window {
    window(window_options options);
    ~window();

    GLFWwindow      * glfw_window;
    window_options    win_options;
};

using window_t = window *;

}

#endif //NAKLUYN_WINDOW_HPP
