#ifndef NAKLUYN_HPP
#define NAKLUYN_HPP

#include <nakluyn/video/context.hpp>
#include <nakluyn/video/window.hpp>
#include <nakluyn/gui/gui.hpp>

namespace nak {

void window_loop(window * window, gui::render_fn gui_callback);

}

#endif