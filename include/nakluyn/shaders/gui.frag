#version 430

in vec2 uvs;

out vec4 frag_color;

uniform sampler2D gui_texture;
uniform vec3 extra_color;

void main() {
    frag_color = vec4(extra_color, 1.0);
}
