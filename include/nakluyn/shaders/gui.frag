#version 430

in vec2 uvs;

out vec4 frag_color;

uniform sampler2D ngtexture;
uniform vec3 extra_color;

void main() {
    vec4 t = texture(ngtexture, uvs);
    frag_color = vec4(mix(extra_color, t.xyz, t.r), t.r);
}
