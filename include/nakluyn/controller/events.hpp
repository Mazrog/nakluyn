//
// Created by mazrog on 30/05/19.
//

#ifndef NAKLUYN_EVENTS_HPP
#define NAKLUYN_EVENTS_HPP

namespace nak::controller {

namespace events {

struct kb_key {
    short key, scancode;
    uint8_t action, mods;
};

struct kb_char {
    unsigned codepoint;
};

struct mouse_pair {
    double x, y;
};

struct mouse_click {
    uint8_t button, action, mods;
    mouse_pair pos;
};

enum EventType {
    KB_KEY,
    KB_CHAR,

    MOUSE_MOVE,
    MOUSE_SCROLL,
    MOUSE_CLICK,

    EVENT_COUNT
};

}

struct event_detail {
    event_detail() {};

    events::EventType type;

    union {
        events::kb_key      key;
        events::kb_char     keychar;
        events::mouse_pair  position;
        events::mouse_pair  scroll;
        events::mouse_click click;
    };
};



}

#endif //NAKLUYN_EVENTS_HPP
