//
// Created by mazrog on 06/05/19.
//

#ifndef NAKLUYN_GUI_HPP
#define NAKLUYN_GUI_HPP

#include <nakluyn/nakluyn.hpp>
#include <glm/glm.hpp>

#include <nakluyn/gui/structs.hpp>
#include <nakluyn/gui/renderer.hpp>
#include <nakluyn/controller/events.hpp>

namespace nak::gui {

struct guibase {
    virtual void fire_event(controller::event_detail const&) = 0;

    std::array<Distance, 2>     position;
    std::array<Distance, 2>     size;
};

template < typename Derived >
struct gui : guibase {
    void fire_event(controller::event_detail const& detail) final {
        return static_cast<Derived &>(*this).on(detail);
    }
};

}

#endif //NAKLUYN_GUI_HPP
