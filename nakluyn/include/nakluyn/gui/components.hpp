//
// Created by mazrog on 13/05/19.
//

#ifndef NAKLUYN_COMPONENTS_HPP
#define NAKLUYN_COMPONENTS_HPP

#include <nakluyn/gui/gui.hpp>

namespace nak::gui {

struct button : gui<button> {

};

struct titlebar : gui<titlebar> {
    titlebar();
    button  minimize;
    button  close;
};

}

#endif //NAKLUYN_COMPONENTS_HPP
