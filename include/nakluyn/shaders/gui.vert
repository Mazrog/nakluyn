#version 430

const vec2 quad[] = vec2[](
    vec2(-1, 1),
    vec2(-1, -1),
    vec2(1, 1),
    vec2(1, -1)
);

out vec2 uv_out;
out vec4 pass_color;

layout (std140, binding = 0) uniform GuiBlock {
    vec2 position;
    vec2 scale;
    vec4 color;
};

void main() {
    vec2 pos = quad[gl_VertexID];
    gl_Position = vec4(pos * scale + position, 0, 1);

    uv_out = vec2(
        (pos.x + 1) / 2.,
        (1 - pos.y) / 2.
    );
    pass_color = color;
}
