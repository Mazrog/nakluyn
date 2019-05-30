//
// Created by mazrog on 12/05/19.
//

#ifndef NAKLUYN_GUI_WINDOW_HPP
#define NAKLUYN_GUI_WINDOW_HPP

#include <nakluyn/gui/components.hpp>

namespace nak::gui {

struct guiwindow {
    guiwindow(window_t window);

    virtual void render() = 0;
    void close();
    void minimize();

    window_t    window;
    UniformBlock<ubo::NakGuiVertBlock>    guiVertBlock{UnifBlock::GUIVERT};
};

struct basewindow : guiwindow {
    basewindow(window_t window);
    void render() override;

    titlebar    bar;
};

}

#endif //NAKLUYN_GUI_WINDOW_HPP
