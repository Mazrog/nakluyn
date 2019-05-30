//
// Created by mazrog on 06/05/19.
//

#ifndef NAKLUYN_GUI_HPP
#define NAKLUYN_GUI_HPP

#include <nakluyn/nakluyn.hpp>
#include <glm/glm.hpp>

#include <nakluyn/gui/structs.hpp>
#include <nakluyn/gui/painter.hpp>

namespace nak::gui {

template < typename T >
class gui {
    using Type = T;

public:
    std::array<Distance, 2>     position;
    std::array<Distance, 2>     size;
};



template < typename T, typename ... Args >
void setup_gui(nak::window_t window, Args && ... args) {
    window->gui_window = std::make_unique<T>(window, std::forward<Args>(args)...);
}

template < typename T >
void paint(guiwindow *, T &&);

}

#endif //NAKLUYN_GUI_HPP
