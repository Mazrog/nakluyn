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
        struct is_function_pointer : std::false_type {};

        template < typename R, typename ... Args >
        struct is_function_pointer<R (*) (Args...)> : std::true_type {};

        template < typename R, typename ... Args >
        using pfunc = R (*) (Args ...);

        template < typename T >
        struct extract_params;

        template < typename R, typename Ev,  typename ... Args >
        struct extract_params<R (*) (Ev, Args ...)> {
            using type = std::tuple<Args...>;
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

        template < typename ... Args >
        void setup(Args && ... args) {
            static_assert(
                    sizeof...(args) > 0 &&
                    sizeof...(args) & 1,
                    "ill formed states"
            );

            build(std::forward<Args>(args)...);
        }

        template < typename ... Args >
        void set_context(Args && ... args) {
            set_context_impl(std::forward<Args>(args)...);
        }

        template < typename ... Args >
        void set_context_impl() {}

        void build(Enum init) {
            current_state = init;
        }

        template < typename ... Args >
        void build(Enum id, action_t action, Args && ... tail) {
            s[static_cast<enum_type_t>(id)] = action;
            build(std::forward<Args>(tail)...);
        }

        void process(event_detail const& event) {
            Enum res_state = s[static_cast<enum_type_t >(current_state)](event);
            current_state = res_state;
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
    void sub_keyboard(window_t win, event_context<Enum, Actions> * listener) {
        event_dispatcher<Enum, Actions>::instance().listener = listener;
        glfwSetKeyCallback(win->glfw_window, key_cb<Enum, Actions>);
    }

    template < typename Enum, typename Actions >
    void unsub(event_context<Enum, Actions> *) {
        event_dispatcher<Enum, Actions>::instance().listener = nullptr;
    }

}

#endif //NAKLUYN_CONTROLLER_HPP
