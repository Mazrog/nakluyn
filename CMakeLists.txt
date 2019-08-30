cmake_minimum_required(VERSION 3.14)
project(nakluyn)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set_target_properties(glfw PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "C:\\msys64\\mingw64\\include"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories(cmake-build-debug)

file(GLOB CPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        nakluyn/src/*.cpp
        nakluyn/src/*/*.cpp
)

file(GLOB HPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        nakluyn/include/nakluyn/*.hpp
        nakluyn/include/nakluyn/*/*.hpp
)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/deps
        ${CMAKE_CURRENT_SOURCE_DIR}/nakluyn/include
)


###############################################################################
# Main library
add_library(${PROJECT_NAME} STATIC
        ${CPP_FILES}
        ${HPP_FILES}
)

target_compile_options(${PROJECT_NAME}
        PRIVATE -std=c++17 -Wall -Wextra -pedantic -O2
)

target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)

target_link_libraries(${PROJECT_NAME}
        PUBLIC glfw OpenGL::GL OpenGL::GLU GLEW::GLEW endora
)

###############################################################################
# Sample executable
add_executable(${PROJECT_NAME}_sample
    sample/main.cpp
)

target_compile_options(${PROJECT_NAME}_sample
        PRIVATE -std=c++17 -Wall -Wextra -pedantic -O2
)

target_link_libraries(${PROJECT_NAME}_sample
        PRIVATE ${PROJECT_NAME}
)

add_dependencies(${PROJECT_NAME}_sample ${PROJECT_NAME})