#version 430
#define M_PI 3.1415926535897932384626433832795

in vec2 uv_out;
in vec4 pass_color;

out vec4 frag_color;

uniform sampler2D gui_texture;
uniform int shape;

void main() {
    float dist = distance(uv_out, vec2(0.5, 0.5));

    if (dist > .5)
        discard;

    frag_color = pass_color; //texture(gui_texture, pass_uvs);
}
