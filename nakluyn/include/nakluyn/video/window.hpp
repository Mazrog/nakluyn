//
// Created by mazrog on 28/04/19.
//

#ifndef NAKLUYN_WINDOW_HPP
#define NAKLUYN_WINDOW_HPP

#include <string>
#include <vector>
#include <memory>

struct GLFWwindow;

namespace nak {

namespace gui { struct guiwindow; }

struct window;
using window_t = window *;

struct window_options {
    std::string title;              // window title
    int width;                      // window width, in pixels
    int height;                     // window height, in pixels
    int depth_bits;                 // number of bits for the depth buffer
    short opengl_version_major;     // major version of opengl requested
    short opengl_version_minor;     // minor version of opengl requested
    bool decorated;                 // if the window has OS border
};

struct window {
    explicit window(window_options options);
    ~window();

    void swap() const;
    void poll_events() const;

    // Utilities functions
    bool should_close() const;
    void should_close(bool should_close);

    GLFWwindow      * glfw_window;
    window_options    win_options;

    window_t                parent;
    std::vector<window_t>   children;

    std::unique_ptr<gui::guiwindow>  gui_window;
};

}

#endif //NAKLUYN_WINDOW_HPP
