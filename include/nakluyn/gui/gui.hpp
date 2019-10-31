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
 * Some forward declarations
 */
struct ngContext;
struct ngDrawCommand;
struct ngVertex;
struct ngDrawList;
struct ngDrawData;
struct ngWindow;


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

    unsigned current_buffer_offset;
    unsigned current_indices_offset;
};

struct ngDrawData {
    std::vector<ngDrawList> draw_lists;
};

struct ngWindow {};

/*
 * Context for the application
 */
struct ngContext {
    bool initialized;

    ngDrawData draw_data;
};

}

#endif //NAKLUYN_GUI_HPP
