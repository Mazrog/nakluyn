//
// Created by mazrog on 28/05/19.
//

#ifndef NAKLUYN_CONTROLLER_HPP
#define NAKLUYN_CONTROLLER_HPP

#include <unordered_map>
#include <GLFW/glfw3.h>
#include <nakluyn/video/window.hpp>
#include <nakluyn/controller/events.hpp>

namespace nak::controller {

    namespace helper {
        template < typename T >
        struct extract_params;

        template < typename R, typename Ev,  typename ... Args >
        struct extract_params<R (*) (Ev, Args ...)> {
            using type = std::tuple<Args...>;
            static constexpr size_t value = sizeof...(Args);
        };
    }

    template <
            typename Enum,
            typename Actions
                    >
    struct event_context {
        using enum_type_t   = std::underlying_type_t<Enum>;
        using action_t      = Actions;
        using func_param_t  = typename helper::extract_params<Actions>::type;

        std::unordered_map<enum_type_t, action_t>   s;
        Enum current_state;
        func_param_t params;

        event_context() = default;

        template < typename ... Args >
        event_context(Args && ... args) : params(std::forward<Args>(args)...) {
            static_assert(std::is_same_v<std::tuple<Args...>, func_param_t>, "No matching constructor with this list of argument.");
        }

        template < typename ... Args >
        void setup(Args && ... args) {
            static_assert(
                    sizeof...(args) > 0 &&
                    sizeof...(args) & 1,
                    "ill formed states"
            );

            build(std::forward<Args>(args)...);
        }

        void build(Enum init) {
            current_state = init;
        }

        template < typename ... Args >
        void build(Enum id, action_t action, Args && ... tail) {
            s[static_cast<enum_type_t>(id)] = action;
            build(std::forward<Args>(tail)...);
        }

        template < typename ... Args >    
        void set_context(Args && ... args) {
            params = std::make_tuple(std::forward<Args>(args)...);
        }

        void process(event_detail const& event) {
            call(static_cast<enum_type_t >(current_state), event);
        }
        
        void call(enum_type_t id, event_detail const& event){
            call_impl(id, event, std::make_index_sequence<helper::extract_params<Actions>::value>{});
        }
        
        template < size_t ... I >
        void call_impl(enum_type_t id, event_detail const& event, std::index_sequence<I...>) {
            current_state = s[id](event, std::get<I>(params)...);
        }
    };

    template < typename Enum, typename Actions >
    struct event_dispatcher {
        static event_dispatcher<Enum, Actions> & instance() {
            static event_dispatcher<Enum, Actions> s_instance;
            return s_instance;
        }

        event_dispatcher() noexcept : listener(nullptr) {}

        event_context<Enum, Actions>    * listener;
    };

    template < typename Enum, typename Actions >
    void key_cb(GLFWwindow *, int key, int, int action, int) {
        event_detail detail;
        detail.type = events::KB_KEY;
        detail.key.key = key; detail.key.action = action;

        auto dispatcher = event_dispatcher<Enum, Actions>::instance().listener;
        if (dispatcher)
            dispatcher->process(detail);
    }

    template < typename Enum, typename Actions >
    void mousemove_cb(GLFWwindow *, double xpos, double ypos) {
        event_detail detail;
        detail.type = events::MOUSE_MOVE;
        detail.position = { xpos, ypos };

        auto dispatcher = event_dispatcher<Enum, Actions>::instance().listener;
        if (dispatcher)
            dispatcher->process(detail);
    }

    template < typename Enum, typename Actions >
    void mouseclick_cb(GLFWwindow *, int button, int action, int mods) {
        event_detail detail;
        detail.type = events::MOUSE_CLICK;
        detail.click.button = button;
        detail.click.action = action;
        detail.click.mods = mods;

        auto dispatcher = event_dispatcher<Enum, Actions>::instance().listener;
        if (dispatcher)
            dispatcher->process(detail);
    }

    template < typename Enum, typename Actions >
    void sub_keyboard(window_t win, event_context<Enum, Actions> * listener) {
        event_dispatcher<Enum, Actions>::instance().listener = listener;
        glfwSetKeyCallback(win->glfw_window, key_cb<Enum, Actions>);
    }

    template < typename Enum, typename Actions >
    void sub_mouse(window_t win, event_context<Enum, Actions> * listener) {
        event_dispatcher<Enum, Actions>::instance().listener = listener;
        glfwSetCursorPosCallback(win->glfw_window, mousemove_cb<Enum, Actions>);
        glfwSetMouseButtonCallback(win->glfw_window, mouseclick_cb<Enum, Actions>);
    }

    template < typename Enum, typename Actions >
    void unsub(event_context<Enum, Actions> *) {
        event_dispatcher<Enum, Actions>::instance().listener = nullptr;
    }

}

#endif //NAKLUYN_CONTROLLER_HPP
