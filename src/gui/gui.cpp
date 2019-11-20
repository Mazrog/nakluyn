//
// Created by mazrog on 13/05/19.
//
#include <nakluyn/gui/gui.hpp>
#include <nakluyn/video/context.hpp>
#include <algorithm>
#include <iostream>

namespace nak::gui {

window::window(nak::gui::window::creation_flags flags)
    : flags(flags),
    pos(0),
    size(0)
{}

context::context() : current_window(nullptr) {}

base_draw_unit::base_draw_unit(const nak::gui::gui_base &base)
    : buffer_index(0),
    texture_id(base.sprite.texture),
    color(base.color),
    clip_rect(0, 0, 1000, 1000)
{}

text_draw_unit::text_draw_unit(const nak::gui::text &t)
    : base_draw_unit(t)
{
    char const * p = t.content.data();
    std::size_t cur = 0;
    std::size_t const size = t.content.size();
    while (cur < size) {
        char const c = *(p + cur);
        unsigned long char_code;
        if (c & 0x80) {
            auto const next = *(p + cur + 1);
            char_code = ((c & 0x03) << 6) | (next & 0x3f);
            cur += 2;
        } else {
            ++cur;
            char_code = c;
        }
        char_codes.push_back(char_code);
    }
}

nak::controller::io * get_io() { return get_context()->io; }

void set_io(controller::io * io) { get_context()->io = io; }

void set_window_context(nak::window * window) { get_context()->options = &window->win_options; }

context * get_context() { return nak::context::s_gui_context.get(); }

draw_data const& get_draw_data() { return get_context()->draw_data; }

glm::vec2 apply_window_scale(glm::vec2 size) {
    auto const options = get_context()->options;
    glm::vec2 const window_size = glm::vec2(
            options->width,
            options->height
    );

    return size / window_size;
}

glm::vec2 compute_window_pos(glm::vec2 pos) {
        glm::vec2 const ogl_pos = apply_window_scale(pos) * 2.f;
        return { ogl_pos.x - 1.f, 1.f - ogl_pos.y };
    }

static window * find_window_by_id(int window_id) {
    context * context = get_context();
    auto const& it = std::find_if(context->windows.begin(),
                                  context->windows.end(),
                                  [window_id] (window const& win) { return win.window_id == window_id; }
    );

    return (it == context->windows.end()) ? nullptr : &*it;
}

static window * create_new_window(int window_id, gui::window::creation_flags flags) {
    context * context = get_context();
    window & window = context->windows.emplace_back(flags);
    window.window_id = window_id;

    window.pos = glm::vec2(20);
    window.temp_data.cursor_start = window.temp_data.cursor_max = window.temp_data.cursor = window.pos;

    return &window;
}

static box compute_window_box(gui::window const& win) {
    float const x = win.pos.x,
            y = win.pos.y,
            w = win.size.x,
            h = win.size.y;
    return box{ glm::vec2(x, y),
                glm::vec2(x, y+h),
                glm::vec2(x+w, y),
                glm::vec2(x+w, y+h)
    };
}

static box compute_box(glm::vec2 const& top_left, glm::vec2 const& bottom_right) {
    float const w = bottom_right.x - top_left.x,
            h = bottom_right.y - top_left.y;
    return box {
            top_left,
            top_left + glm::vec2(0, h),
            top_left + glm::vec2(w, 0),
            top_left + glm::vec2(w, h),
    };
}

static bool point_in_box(glm::vec2 const& point, box const& b) {
    float const x1 = b[0].x,
            y1 = b[0].y,
            x2 = b[3].x,
            y2 = b[3].y;
    return (point.x >= x1 && point.x <= x2) && (point.y >= y1 && point.y <= y2);
}


void new_frame() {
    context * context = get_context();
    context->draw_data.lists.clear();
}

static gui_base push_window(gui::window const& win) {
    gui_base base {
            compute_window_box(win),
            {
                    {
                            glm::vec2(0, 0),
                            glm::vec2(0, 1),
                            glm::vec2(1, 0),
                            glm::vec2(1, 1)
                    },
                    0
            },
            {.3, .4, .6}
    };

    return base;
}

static void register_base_draw_unit(gui_base const& base, std::size_t buffer_index, draw_list & drawlist) {
    base_draw_unit drawunit(base);
    drawunit.buffer_index = buffer_index;
    for (std::size_t i = 0; i < base.position.size(); ++i) {
        drawlist.buffer.emplace_back(compute_window_pos(base.position[i]), base.sprite.uvs[i]);
    }
    drawlist.units.push_back(std::move(drawunit));
}

static void register_text_draw_unit(text const& , std::size_t , draw_list &) {}

void render() {
    // all items are drawn, we construct the final draw_data;
    context * ctx = get_context();
    auto & drawdata = ctx->draw_data;
    for (auto const& win: ctx->windows) {
        draw_list drawlist;
        std::size_t buffer_index = 0;

        {
            // we register the window in the draw list
            auto const wbase = push_window(win);
            register_base_draw_unit(wbase, buffer_index, drawlist);
            buffer_index += 4;
        }

        for (auto const& el: win.temp_data.elements) {
            std::visit(utils::overloaded {
                [buffer_index, &drawlist] (gui_base const& base) { return register_base_draw_unit(base, buffer_index, drawlist); },
                [buffer_index, &drawlist] (text const& t) { return register_text_draw_unit(t, buffer_index, drawlist); }
                },
                el
            );
            buffer_index += 4;
        }

        drawdata.lists.push_back(std::move(drawlist));
    }
}

bool begin(int window_id, gui::window::creation_flags flags) {
    context * context = get_context();

     window * window = find_window_by_id(window_id);
     bool const window_just_created = !window;

     if (window_just_created) {
        window = create_new_window(window_id, flags);
     }

     context->current_window = window;
     window->size = glm::vec2(120.f);

    return true;
}

void end() {

}

bool button(std::string const& label) {
    context * context = get_context();
    controller::io * const io = get_io();

    float const labelsize = label.size() * 13;
    glm::vec2 const start = context->current_window->temp_data.cursor + glm::vec2(5, 3), // padding
        bottom_right = start + glm::vec2(labelsize, 30) + glm::vec2(5, 3);

    box btn_box = compute_box(start, bottom_right);
    gui_base btn {
        btn_box,
        {
                {
                        glm::vec2(0, 0),
                        glm::vec2(0, 1),
                        glm::vec2(1, 0),
                        glm::vec2(1, 1)
                },
                0
        },
        {.7, .3, .6}
    };

    bool const hovered = point_in_box(io->mouse().mouse_pos, btn_box);
    if (hovered) {
        btn.color.g = .9;
    }

    context->current_window->temp_data.elements.push_back(std::move(btn));

    return hovered;
}

}