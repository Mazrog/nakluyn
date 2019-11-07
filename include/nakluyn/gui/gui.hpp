//
// Created by mazrog on 06/05/19.
//

#ifndef NAKLUYN_GUI_HPP
#define NAKLUYN_GUI_HPP

#include <vector>
#include <optional>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace nak::gui {
/*
 * Some forward declarations
 */
struct io;
struct draw_command;
struct vertex;
struct draw_list;
struct draw_data;
struct window;
struct context;

using render_fn = void (*)();
using index_t = unsigned short;

struct init_gui_t {};
inline constexpr init_gui_t init_gui {};

struct io {
    // input
    glm::vec2 mouse_pos;

    bool want_capture_mouse;    // if the gui app wants the mouse
    bool want_capture_keyboard; // if the gui app wants the keyboard

    io() : want_capture_mouse(false), want_capture_keyboard(false) {}
};

struct draw_command {
    unsigned buffer_offset;
    unsigned indices_offset;
    unsigned vertices_count;
};

struct vertex {
    glm::vec2 pos;
    glm::vec2 uvs;
    glm::vec4 color;
};

struct draw_list {
    std::vector<draw_command> commands;
    std::vector<index_t>  indices;
    std::vector<vertex> vertices;

    unsigned current_buffer_offset;
    unsigned current_indices_offset;
};

struct draw_data {
    std::vector<draw_list> draw_lists;
};

struct window {
    enum creation_flags {
        empty       = 1 << 0,
        header      = 1 << 1,
        footer      = 1 << 2
    };

    window(window::creation_flags flags = creation_flags::empty);

    int window_id;
    creation_flags flags;
    glm::vec2   cursor;
};

/*
 * Context for the application
 */
struct context {
    std::vector<window> windows;
    draw_data           draw_data;

    io  io;

    context();
};

/*
 * API
 */

context * get_context();
draw_data const& get_draw_data();

void new_frame();

bool begin(int window_id);
void end();
bool button();

}

#endif //NAKLUYN_GUI_HPP
