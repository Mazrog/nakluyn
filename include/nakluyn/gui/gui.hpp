//
// Created by mazrog on 06/05/19.
//

#ifndef NAKLUYN_GUI_HPP
#define NAKLUYN_GUI_HPP

#include <vector>

#include <nakluyn/nakluyn.hpp>
#include <nakluyn/gui/helper.hpp>
#include <glm/vec4.hpp>

namespace nak::gui {
/*
 * Context for the application
 */
struct ngContext {
    bool initialized;

};

struct ngDrawCommand {
    unsigned buffer_offset;
    unsigned indices_offset;
    unsigned vertices_count;
};

using index_t = unsigned short;

struct ngVertex {
    glm::vec2 pos;
    glm::vec2 uvs;
    glm::vec4 color;
};

struct ngDrawList {
    std::vector<ngDrawCommand> commands;
    std::vector<index_t>  indices;
    std::vector<ngVertex> vertices;
};

struct ngDrawData {};

struct ngWindow {};

}

#endif //NAKLUYN_GUI_HPP
