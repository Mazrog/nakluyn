//
// Created by mazrog on 01/05/19.
//

#ifndef NAKLUYN_CONTEXT_HPP
#define NAKLUYN_CONTEXT_HPP

#include <memory>
#include <nakluyn/gui/gui.hpp>

namespace nak {
struct context {
    context();
    context(gui::init_gui_t);
    ~context();

    static std::unique_ptr<gui::ngContext> s_gui_context;
};
}

#endif //NAKLUYN_CONTEXT_HPP
