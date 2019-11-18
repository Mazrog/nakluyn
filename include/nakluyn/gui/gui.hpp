//
// Created by mazrog on 06/05/19.
//

#ifndef NAKLUYN_GUI_HPP
#define NAKLUYN_GUI_HPP

#include <vector>
#include <optional>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <nakluyn/controller/io.hpp>

namespace nak::gui {
/*
 * Some forward declarations
 */
struct element;
struct draw_data;
struct window;
struct context;

/* Tag value for nakluyn context creation */
struct init_gui_t {};
inline constexpr init_gui_t init_gui {};
/* --------------------- */

struct element {
    struct shader_block {
        // pos and size are in window coordinates
        glm::vec4 vertex;
        glm::vec4 color;
        glm::vec2 size;
    };

    shader_block block;

    glm::vec4 clip_rect;
};

struct draw_list {
    std::vector<element>    elements;
    std::vector<float>      buffer;
};

struct draw_data {
    std::vector<draw_list> lists;
};

struct window_internal {
    glm::vec2   cursor;
    glm::vec2   cursor_start;   // begin area with window padding
    glm::vec2   cursor_max;     // maximum right bottom corner ~ content size
};

struct window {
    enum creation_flags {
        empty       = 1 << 0,
        header      = 1 << 1,
        footer      = 1 << 2
    };

    window(window::creation_flags flags);

    int window_id;
    creation_flags flags;
    window_internal  temp_data;
    glm::vec2   pos;
    glm::vec2   size;
};

/*
 * Context for the application
 */
struct context {
    std::vector<window> windows;
    window *            current_window;
    gui::draw_data      draw_data;

    controller::io      * io;

    context();
};

/*
 * API
 */

context * get_context();
controller::io * get_io();
draw_data const& get_draw_data();

void new_frame();
void render();

bool begin(int window_id, gui::window::creation_flags flags = gui::window::creation_flags::empty);
void end();

bool button(const char * label);

}

#endif //NAKLUYN_GUI_HPP
