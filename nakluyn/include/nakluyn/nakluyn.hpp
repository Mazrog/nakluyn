#ifndef NAKLUYN_HPP
#define NAKLUYN_HPP

#include "nakluyn/video/context.hpp"
#include "nakluyn/video/registry.hpp"
#include "nakluyn/video/window.hpp"

namespace nak {

window_t make_window(window_options const& options, window_t parent = nullptr);

void window_loop(window_t window);

}

#endif