#version 430

out vec2 pass_uvs;
out vec4 pass_color;

layout (std140, binding = 0) uniform GuiBlock {
    vec2 position;
    vec2 uvs;
    vec4 color;
};

uniform mat4 transform;

void main() {
    pass_uvs = uvs;
    pass_color = color;
    gl_Position = transform * vec4(position, 0, 1);
}
