//
// Created by mazrog on 13/05/19.
//

#ifndef NAKLUYN_COMPONENTS_HPP
#define NAKLUYN_COMPONENTS_HPP

#include <nakluyn/gui/gui.hpp>

namespace nak::gui {

struct button : gui<button> {
    glm::vec3 color;

    void on(controller::event_detail const& detail);
    friend void draw(button & btn, guiwindow * window);
};

struct titlebar : gui<titlebar> {
    titlebar();
    button  minimize;
    button  close;

    glm::vec3 color;

    void on(controller::event_detail const& detail);
    friend void draw(titlebar & titlebar, guiwindow * window);
};

}

#endif //NAKLUYN_COMPONENTS_HPP
