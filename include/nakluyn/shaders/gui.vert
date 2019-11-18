#version 430

layout (location = 0) in vec4 vertex;

out vec2 uvs;

void main() {
    gl_Position = vec4(vertex.xy, 0, 1);

    uvs = vertex.zw;
}
