//
// Created by mazrog on 25/05/19.
//

#include <nakluyn/gui/components.hpp>

namespace nak::gui {

void button::on(const nak::controller::event_detail &) {
    puts("button on");
}

titlebar::titlebar() {
    size = { 600, 30 };
    position = { 0, 0 };
    color = glm::vec3(.3, .7, .4);

    close.size = {30, 30};
    close.position = {300, 0};
    close.color = glm::vec3(0.86, 0.08, 0.24);
}

void titlebar::on(const nak::controller::event_detail & detail) {
    double x = detail.position.x, y = detail.position.y,
            tx = close.position[0], ty = close.position[1],
            tw = close.size[0], th = close.size[1];
    bool close_cond = (x >= tx) && (x <= tx + tw) && (y >= ty) && (y <= ty + th);
    if (close_cond) {
        return close.on(detail);
    }
}

}