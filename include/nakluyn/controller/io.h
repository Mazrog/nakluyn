//
// Created by Maxime.Cabanal-Duvil on 11/8/2019.
//

#ifndef NAKLUYN_IO_H
#define NAKLUYN_IO_H

#include <string>

namespace nak::controller {
using wchar = unsigned short;

enum MouseButton {
    LEFT, RIGHT, MIDDLE,
    MB_COUNT
};

enum KBModifiers {
    CTRL, SHIFT, ALT,
    KBM_COUNT
};

struct io {
    // input
    glm::vec2 mouse_pos;
    bool mouse_down[MouseButton::MB_COUNT];
    bool keyboard_modifiers[KBModifiers::KBM_COUNT];
    bool key_down[512];

    bool want_capture_mouse;    // if the gui app wants the mouse
    bool want_capture_keyboard; // if the gui app wants the keyboard

    std::string characters_queue;   // UTF-8 chars !

    io() : want_capture_mouse(false), want_capture_keyboard(false) {}

    void push_char(char c) { characters_queue.push_back(c); }
    void clear_char_queue() { characters_queue.clear(); }
};
}

#endif //NAKLUYN_IO_H
