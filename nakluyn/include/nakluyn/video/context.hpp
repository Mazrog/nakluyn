//
// Created by mazrog on 01/05/19.
//

#ifndef NAKLUYN_CONTEXT_HPP
#define NAKLUYN_CONTEXT_HPP

namespace nak {
struct context {
    context();
    ~context();

    void glew_init() const;
};
}

#endif //NAKLUYN_CONTEXT_HPP