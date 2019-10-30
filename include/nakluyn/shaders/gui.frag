#version 430

in vec2 pass_uvs;
in vec4 pass_color;

out vec4 frag_color;

uniform sampler2D gui_texture;

void main() {
    frag_color = color * texture(gui_texture, pass_uvs);
}
