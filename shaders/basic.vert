#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;

out vec3 color;
out vec2 v_texture;

void main() {
    gl_Position = position;
    color = vec3(position.x + 0.5, 1.0, position.y + 0.5);

    v_texture = texCoord;
}