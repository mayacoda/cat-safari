#version 330 core

layout(location = 0) out vec4 out_color;

in vec3 color;
in vec2 v_texture;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main() {
    vec4 texColor = texture(u_texture, v_texture);
    float r = texColor[0] * texColor[3] + color[0] * (1 - texColor[3]);
    float g = texColor[1] * texColor[3] + color[1] * (1 - texColor[3]);
    float b = texColor[2] * texColor[3] + color[2] * (1 - texColor[3]);
    float a = texColor[3] * texColor[3] + 1 - texColor[3];
    out_color =  vec4(r, g, b, a);
}
