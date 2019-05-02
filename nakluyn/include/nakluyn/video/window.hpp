//
// Created by mazrog on 28/04/19.
//

#ifndef NAKLUYN_WINDOW_HPP
#define NAKLUYN_WINDOW_HPP

#include <string>
#include <vector>

struct GLFWwindow;

namespace nak {

struct window;
using window_t = window *;
using flag_t = uint64_t;

enum window_flags : flag_t {
    NONE,
    DEPTH       = 0x01,         // enable depth test
    BLEND       = 0x02          // enable blending mode
};

struct window_options {
    std::string title;              // window title
    flag_t  flags;                  // flags to set some opengl options
    int width;                      // window width, in pixels
    int height;                     // window height, in pixels
    int depth_bits;                 // number of bits for the depth buffer
    short opengl_version_major;     // major version of opengl requested
    short opengl_version_minor;     // minor version of opengl requested
};

struct window {
    window(window_options options);
    ~window();

    void apply_flags();

    GLFWwindow      * glfw_window;
    window_options    win_options;

    window_t                parent;
    std::vector<window_t>   children;
};

}

#endif //NAKLUYN_WINDOW_HPP
