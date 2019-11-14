#version 430
#define M_PI 3.1415926535897932384626433832795

in vec2 uv_out;
in vec4 pass_color;
flat in int  pass_shape;

out vec4 frag_color;

uniform sampler2D gui_texture;

vec4 circle() {
    float dist = distance(uv_out, vec2(0.5, 0.5));

    if (dist > .5)
        discard;

    return pass_color;
}

vec4 choose_color() {
    switch (pass_shape) {
        case 0: return pass_color;
        case 1: return circle();
    }
    discard;
}

void main() {
    frag_color = choose_color();
}
