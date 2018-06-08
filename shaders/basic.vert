#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec3 color;
out vec2 v_texture;

uniform mat4 u_transformationMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;

void main() {
    gl_Position = u_projectionMatrix * u_viewMatrix * u_transformationMatrix * position;
    color = vec3(position.x + 0.5, 1.0, position.y + 0.5);

    v_texture = texCoord;
}