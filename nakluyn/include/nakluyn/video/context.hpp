//
// Created by mazrog on 01/05/19.
//

#ifndef NAKLUYN_CONTEXT_HPP
#define NAKLUYN_CONTEXT_HPP

struct GLFWwindow;

namespace nak {
struct context {
    context();
    ~context();

private:
    GLFWwindow      * _hidden_window;
};
}

#endif //NAKLUYN_CONTEXT_HPP
