//
// Created by mazrog on 13/05/19.
//
#include <nakluyn/gui/gui.hpp>
#include <nakluyn/video/context.hpp>

namespace nak::gui {

inline ngContext * get_context() {
    return nak::context::s_gui_context.get();
}

ngDrawData const& get_draw_data() {
    ngContext * context = get_context();
    return context->draw_data;
}

}