#version 430

in vec2 pass_uvs;

out vec4 frag_color;

uniform sampler2D gui_texture;

layout (std140, binding = 0) uniform GuiBlock {
    vec2 position;
    vec2 scale;
    vec3 color;
};

void main() {
    frag_color = vec4(color, .6);
    // color = texture(gui_texture, pass_uvs);
}
