//
// Created by mazrog on 13/05/19.
//
#include <nakluyn/gui/gui_window.hpp>
#include <GL/glew.h>
#include <endora/utils.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace nak::gui {

template <>
void paint(guiwindow * window, titlebar & titlebar) {
    glm::vec2 position(titlebar.position[0], titlebar.position[1]);
    glm::vec2 scale(titlebar.size[0] * 2 / 1600., titlebar.size[1] * 2.0 / 900.);

    window->guiVertBlock.set(ubo::NakGuiVertBlock::fields::position, glm::value_ptr(position));
    window->guiVertBlock.set(ubo::NakGuiVertBlock::fields::scale, glm::value_ptr(scale));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); endora_error("draw call");
}

}