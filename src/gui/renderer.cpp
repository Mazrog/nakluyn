//
// Created by mazrog on 13/05/19.
//
#include <nakluyn/gui/gui_window.hpp>
#include <GL/glew.h>
#include <extern/endora.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace nak::gui {

static void draw_standard(guiwindow * window, glm::vec2 const& position, glm::vec2 const& scale, glm::vec3 const& color) {
    window->guiVertBlock.set(ubo::NakGuiVertBlock::fields::position, glm::value_ptr(position));
    window->guiVertBlock.set(ubo::NakGuiVertBlock::fields::scale, glm::value_ptr(scale));
    window->guiVertBlock.set(ubo::NakGuiVertBlock::fields::color, glm::value_ptr(color));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); endora_error("draw call");
}

void draw(titlebar & titlebar, guiwindow * window) {
    glm::vec2 win(window->window->win_options.width, window->window->win_options.height);
    glm::vec2 position = helpers::pos_from_glfw(titlebar.position[0], titlebar.position[1], win);
    glm::vec2 scale(titlebar.size[0] / win.x, titlebar.size[1] / win.y);

    draw_standard(window, position, scale, titlebar.color);
    draw(titlebar.close, window);
}

void draw(button & btn, guiwindow * window) {
    glm::vec2 win(window->window->win_options.width, window->window->win_options.height);
    glm::vec2 position = helpers::pos_from_glfw(btn.position[0], btn.position[1], win);
    glm::vec2 scale(btn.size[0] / win.x, btn.size[1] / win.y);

    draw_standard(window, position, scale, btn.color);
}

}