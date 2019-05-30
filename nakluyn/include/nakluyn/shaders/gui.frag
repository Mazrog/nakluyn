#version 430

in vec2 pass_uvs;

out vec4 color;

uniform sampler2D gui_texture;


void main() {
    color = vec4(.3, .7, .4, 1.);
    // color = texture(gui_texture, pass_uvs);
}
