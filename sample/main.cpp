#include <nakluyn/nakluyn.hpp>

#include <GL/glew.h>
#include <thread>
#include <chrono>

int main() {
    nak::context context;

    nak::window_options options{
            "Nakluyn sample",
            600,
            400,
            24,
            4, 5,
            true
    };

    nak::window window(options);

    while (!window.should_close()) {
        window.poll_events();

        glClear(GL_COLOR_BUFFER_BIT);

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        window.swap();
    }

    return 0;
}

