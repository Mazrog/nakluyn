//
// Created by mazrog on 01/05/19.
//

#ifndef NAKLUYN_REGISTRY_HPP
#define NAKLUYN_REGISTRY_HPP

#include <memory>
#include <vector>

namespace nak {
struct window;
struct context;

struct registry {
    static registry & instance () {
        static registry s_instance;
        return s_instance;
    }

    void register_window(std::shared_ptr<window> window) {
        _windows.push_back(std::move(window));
    }

private:
    registry() noexcept = default;
    ~registry() = default;

    friend class context;

    void clear() {
        _windows.clear();
    }

private:
    std::vector<std::shared_ptr<window>>  _windows;
    std::shared_ptr<window>               _mother_window;
};

}

#endif //NAKLUYN_REGISTRY_HPP
