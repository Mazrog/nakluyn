//
// Created by mazrog on 01/05/19.
//

#ifndef NAKLUYN_LOGGER_HPP
#define NAKLUYN_LOGGER_HPP

#include <iostream>
#include <GL/glew.h>
// #define FMT_UDL_TEMPLATE 0
#include "spdlog/spdlog.h"

#define gl_error(message, ...) \
    nak::log::get_error(__FILE__, __LINE__, message, ##__VA_ARGS__)

#ifdef TEST_COMPILE
namespace spdlog {
template<typename... Args> void info(char const *, Args && ...) {}
template<typename... Args> void warn(char const *, Args && ...) {}
template<typename... Args> void error(char const *, Args && ...) {}
template<typename... Args> void critical(char const *, Args && ...) {}
}
#endif

namespace nak::log {

enum ErrorStatus {
    GLFW_WINDOW_ERROR   = 0x01
};

enum class level {
    INFO,
    WARNING,
    _ERROR,
    CRITICAL
};


template<typename... Args>
void log(level loglevel, char const * fmt, Args &&... args) {
    switch (loglevel) {
        case level::INFO:       spdlog::info(fmt, std::forward<Args>(args)...); break;
        case level::WARNING:    spdlog::warn(fmt, std::forward<Args>(args)...); break;
        case level::_ERROR:      spdlog::error(fmt, std::forward<Args>(args)...); break;
        case level::CRITICAL:   spdlog::critical(fmt, std::forward<Args>(args)...); break;
    }
}

template < typename ... Args >
void get_error(const char * file, int line, char const * message, Args &&... args) {
    GLenum err;
    if((err = glGetError() ) != GLEW_OK){
        log(
                level::_ERROR,
                "ENDORA OPENGL ERROR -------- {}\nCalled from {} at line {}\nError ({}): {} -- {}\n",
                message, file, line, glewGetErrorString(err), gluErrorString(err)
        );
        if constexpr (sizeof...(args)) {
            ((std::cerr << args << " "), ...) << '\n' << std::endl;
        }
    }
}

}

#endif //NAKLUYN_LOGGER_HPP
