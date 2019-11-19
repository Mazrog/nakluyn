//
// Created by mazrog on 06/05/19.
//

#ifndef NAKLUYN_GUI_HPP
#define NAKLUYN_GUI_HPP

#include <vector>
#include <variant>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <nakluyn/controller/io.hpp>
#include <nakluyn/video/window.hpp>
#include <array>

namespace nak::gui {
namespace utils {
    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
}

/*
 * Some forward declarations
 */
struct sprite_info;
struct gui_base;
struct text;
struct base_draw_unit;
struct text_draw_unit;
struct window;
struct context;

/* Tag value for nakluyn context creation */
struct init_gui_t {};
inline constexpr init_gui_t init_gui {};
/* --------------------- */

using vertex  = glm::vec4;
using box     = std::array<glm::vec2, 4>;
using draw_unit = std::variant<base_draw_unit, text_draw_unit>;
using gui_element = std::variant<gui_base, text>;

struct texture_atlas {};

/* Final draw data */
struct base_draw_unit {
    std::size_t buffer_index;
    unsigned  texture_id;
    glm::vec3 color;
    glm::vec4 clip_rect;
};

struct text_draw_unit : base_draw_unit {
    std::vector<unsigned long> char_codes;
};

struct draw_list {
    std::vector<vertex>    buffer;
    std::vector<draw_unit> units;
};

struct draw_data {
    std::vector<draw_list> lists;
};
/* --------------------------------- */

/* Logic stuff */
struct sprite_info {
    box uvs;
    unsigned texture;
};

struct gui_base {
    box         position;
    sprite_info sprite;
    glm::vec3   color;
};

struct text : gui_base {
    std::string content;
};
/* ----------------------------------------- */
struct window_internal {
    glm::vec2   cursor;
    glm::vec2   cursor_start;   // begin area with window padding
    glm::vec2   cursor_max;     // maximum right bottom corner ~ content size

    std::vector<gui_element>    elements;
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
    window_options      * options;

    context();
};

/*
 * API
 */

context * get_context();
controller::io * get_io();
void set_io(controller::io * io);
void set_window_context(nak::window * window);
draw_data const& get_draw_data();

/* window scaling */
glm::vec2 apply_window_scale(glm::vec2 size);
glm::vec2 compute_window_pos(glm::vec2 pos);
/* ------------------------------------------- */

void new_frame();
void render();

bool begin(int window_id, gui::window::creation_flags flags = gui::window::creation_flags::empty);
void end();

bool button(std::string const& label);

}

#endif //NAKLUYN_GUI_HPP
