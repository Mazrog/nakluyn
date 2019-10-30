//
// Created by Maxime.Cabanal-Duvil on 10/30/2019.
//

#include <nakluyn/gui/opengl_glfw_impl.h>

nak::gui::glContext::glContext() {
    using namespace endora::ecs;

    gui_prog = create_program(
            create_shader(GL_VERTEX_SHADER, "include/nakluyn/shaders/gui.vert"),
            create_shader(GL_FRAGMENT_SHADER, "include/nakluyn/shaders/gui.frag")
    );
    create_buffers(buffers, BUFFERCOUNT);
    unif_transform = create_uniform(gui_prog, "transform");
    unif_texture = create_uniform(gui_prog, "gui_texture");

    use_program(gui_prog);
}

nak::gui::glContext::~glContext() {
    using namespace endora::ecs;
    destroy_buffers(buffers, BUFFERCOUNT);
    destroy_program(gui_prog);
}
