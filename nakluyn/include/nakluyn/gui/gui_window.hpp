//
// Created by mazrog on 12/05/19.
//

#ifndef NAKLUYN_GUI_WINDOW_HPP
#define NAKLUYN_GUI_WINDOW_HPP

#include <nakluyn/gui/components.hpp>
#include <nakluyn/controller/events.hpp>
#include <endora/structs/vao.hpp>
#include <endora/program.hpp>

namespace nak::gui {

struct guiwindow {
    guiwindow(window_t window);

    virtual void render() = 0;
    virtual void on(controller::event_detail const&) = 0;

    void close();
    void minimize();

    window_t    window;
    UniformBlock<ubo::NakGuiVertBlock>    guiVertBlock{UnifBlock::GUIVERT};
    Vao     vao;
    ShaderProgram gui_prog;
};

struct basewindow : guiwindow {
    using guiwindow::guiwindow;

    void render() final;
    void on(controller::event_detail const& detail) final;

    titlebar    bar;
};


template < typename T, typename ... Args >
void setup_gui(nak::window_t window, Args && ... args) {
    window->gui_window = std::make_unique<T>(window, std::forward<Args>(args)...);
    window->gui_window->window = window;
}

}

#endif //NAKLUYN_GUI_WINDOW_HPP
