//
// Created by Maxime.Cabanal-Duvil on 11/8/2019.
//

#ifndef NAKLUYN_IO_H
#define NAKLUYN_IO_H

#include <string>
#include <glm/vec2.hpp>

namespace nak {
    struct window;
}

namespace nak::controller {

enum MouseButton {
    LEFT, RIGHT, MIDDLE,
    MB_COUNT
};

struct mouse_view {
    glm::vec2 mouse_pos;
    bool mouse_down[MouseButton::MB_COUNT];
};

enum KBModifiers {
    SHIFT   = 0x01,
    CTRL    = 0x02,
    ALT     = 0x04,

    KBM_MAX
};

struct keyboard_view {
    bool keyboard_modifiers[KBModifiers::KBM_MAX];
    bool key_down[512];

    std::string characters_queue;   // UTF-8 chars !

    void push_char(char c) { characters_queue.push_back(c); }
    void clear_char_queue() { characters_queue.clear(); }
};

struct io {
    bool want_capture_mouse;    // if the gui app wants the mouse
    bool want_capture_keyboard; // if the gui app wants the keyboard

    mouse_view const& mouse();
    keyboard_view const& keyboard();

    nak::window const& window;

    io(nak::window const& window);
};

}

#endif //NAKLUYN_IO_H
