//
// Created by mazrog on 13/05/19.
//
#include <nakluyn/gui/gui.hpp>
#include <nakluyn/video/context.hpp>
#include <algorithm>

namespace nak::gui {

window::window(nak::gui::window::creation_flags flags)
    : flags(flags),
    pos(0),
    size(0)
{}

context::context() : current_window(nullptr) {}

nak::controller::io * get_io() {
    return get_context()->io;
}

context * get_context() {
    return nak::context::s_gui_context.get();
}

draw_data const& get_draw_data() {
    context * context = get_context();
    return context->draw_data;
}

void new_frame() {}

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

    window.pos = glm::vec2(100, 100);
    window.temp_data.cursor_start = window.temp_data.cursor_max = window.pos;

    return &window;
}

bool begin(int window_id, gui::window::creation_flags flags) {
    context * context = get_context();

     window * window = find_window_by_id(window_id);
     bool const window_just_created = !window;

     if (window_just_created) {
        window = create_new_window(window_id, flags);
     }

     context->current_window = window;

     if (!window_just_created) {

     }

    return true;
}

void end() {

}

bool button(const char * ) {

    return false;
}

}