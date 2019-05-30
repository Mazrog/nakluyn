#version 430

const vec2 quad[] = vec2[](
    vec2(-1, -1),
    vec2(-1, 1),
    vec2(1, -1),
    vec2(1, 1)
);

out vec2 pass_uvs;

layout (std140, binding = 0) uniform GuiBlock {
    vec2 position;
    vec2 scale;
};


void main() {
    gl_Position = vec4(quad[gl_VertexID] * scale / 2., 0., 1.);

    gl_Position.xy += position + vec2(-1, 1) * (1 - scale / 2.);

    pass_uvs = vec2(
        (quad[gl_VertexID].x + 1.) / 2.,
        (quad[gl_VertexID].y + 1.) / 2.
    );
}
