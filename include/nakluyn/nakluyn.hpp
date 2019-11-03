#ifndef NAKLUYN_HPP
#define NAKLUYN_HPP

#include <nakluyn/video/context.hpp>
#include <nakluyn/video/registry.hpp>
#include <nakluyn/video/window.hpp>
#include <nakluyn/gui/gui.hpp>

namespace nak {

window_t make_window(window_options const& options, window_t parent);

void window_loop(window_t window, gui::gui_render_fn gui_callback);

}

#endif