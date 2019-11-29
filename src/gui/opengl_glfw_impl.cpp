//
// Created by Maxime.Cabanal-Duvil on 10/30/2019.
//

#include <nakluyn/gui/opengl_glfw_impl.hpp>
#include <nakluyn/video/window.hpp>

namespace nak::gui::impl {

/* Setting up OpenGL context */
gl_context::gl_context() {
    using namespace endora::ecs;

    gui_prog = create_program(
            create_shader(GL_VERTEX_SHADER, "include/nakluyn/shaders/gui.vert"),
            create_shader(GL_FRAGMENT_SHADER, "include/nakluyn/shaders/gui.frag")
    );
    use_program(gui_prog);

    data_vao = create_vertexarray();
    bind_vertex_array(data_vao);

    create_buffers(buffers, BUFFERCOUNT);
    bind_buffer(buffers[DATABUFFER], GL_ARRAY_BUFFER);
    format_buffer_index_data(0, 4, GL_FLOAT, 0, nullptr);

    font_vao = create_vertexarray();
    bind_vertex_array(font_vao);

    bind_buffer(buffers[FONTBUFFER], GL_ARRAY_BUFFER);
    format_buffer_index_data(0, 4, GL_FLOAT, 0, nullptr);

    unif_texture = create_uniform(gui_prog, "ngtexture");
    unif_extracolor = create_uniform(gui_prog, "extra_color");
    send_uniform(unif_texture, texture_slot);

    font_texture = create_texture();
    bind_texture(font_texture, GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    white = create_texture();
    bind_texture(white, GL_TEXTURE_2D);
    float wh[] = { 1.f, 1.f, 1.f, 1.f };
    load_2D_surface(GL_TEXTURE_2D, 1, 1, wh, GL_RGBA, GL_RGBA, GL_FLOAT);
}

gl_context::~gl_context() {
    using namespace endora::ecs;
    destroy_buffers(buffers, BUFFERCOUNT);
    destroy_vertex_array(data_vao);
    destroy_vertex_array(font_vao);
    destroy_texture(font_texture);
    destroy_program(gui_prog);
}

/* Setting up the gui context custom implementation */
gui_context_impl::gui_context_impl() {}

void gui_context_impl::new_frame() {}

void render_quad(gl_context & glctx, base_draw_unit const& base_unit) {
    using namespace endora::ecs;
    bind_vertex_array(glctx.data_vao);
    check_bind_buffer(glctx.buffers[gl_context::Buffers::DATABUFFER], GL_ARRAY_BUFFER);
    send_uniform(glctx.unif_extracolor, base_unit.color);
    bind_texture(glctx.white, GL_TEXTURE_2D);

    glScissor(base_unit.clip_rect.x, base_unit.clip_rect.y, base_unit.clip_rect.z, base_unit.clip_rect.w);
    glDrawArrays(GL_TRIANGLE_STRIP, base_unit.buffer_index, 4);
}

void render_text(gl_context & glctx, text_draw_unit const& text_unit) {
    using namespace endora::ecs;
    bind_vertex_array(glctx.font_vao);
    check_bind_buffer(glctx.buffers[gl_context::Buffers::FONTBUFFER], GL_ARRAY_BUFFER);
    send_uniform(glctx.unif_extracolor, text_unit.color);
    bind_texture(glctx.font_texture, GL_TEXTURE_2D);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glScissor(text_unit.clip_rect.x, text_unit.clip_rect.y, text_unit.clip_rect.z, text_unit.clip_rect.w);

    set_fontsize(13);

    glm::vec2 cur_pos(0.);
    glm::vec2 const scaling = apply_window_scale(glm::vec2(2.));

    for (auto const& charcode : text_unit.char_codes) {
        auto const g = load_character(charcode);
        load_2D_surface(GL_TEXTURE_2D, g->bitmap.width, g->bitmap.rows, g->bitmap.buffer,
                        GL_RED, GL_RED, GL_UNSIGNED_BYTE);

        float x2 = cur_pos.x + g->bitmap_left * scaling.x;
        float y2 = cur_pos.y + g->bitmap_top * scaling.y;
        float w = g->bitmap.width * scaling.x;
        float h = g->bitmap.rows * scaling.y;

        GLfloat box[16] = {
                x2, y2,         0, 0,
                x2, y2 - h,     0, 1,
                x2 + w, y2,     1, 0,
                x2 + w, y2 - h, 1, 1
        };

        set_buffer_data(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        cur_pos.x += (g->advance.x / 64.f) * scaling.x;
        cur_pos.y += (g->advance.y / 64.f) * scaling.y;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void gui_context_impl::render_ngdraw_data(draw_data const& data) {
    using namespace endora::ecs;
    bind_vertex_array(gl_context.data_vao);

    for (auto const& list : data.lists) {
        bind_buffer(gl_context.buffers[gl_context::Buffers::DATABUFFER], GL_ARRAY_BUFFER);
        set_buffer_data(GL_ARRAY_BUFFER, list.buffer.size() * sizeof(gui::vertex), list.buffer.data(), GL_DYNAMIC_DRAW);

        for (auto const& unit : list.units) {
            std::visit(utils::overloaded {
                [this] (base_draw_unit const& base_unit) { render_quad(gl_context, base_unit); },
                [this] (text_draw_unit const& text_unit) { render_text(gl_context, text_unit); },
                },
                unit
            );
        }
    }
}

}