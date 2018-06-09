#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 v_texture;
out vec3 v_surfaceNormal;
out vec3 v_toLightVector;

uniform mat4 u_transformationMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform vec3 u_lightPosition;


void main() {

    vec4 worldPosition = u_transformationMatrix * position;

    gl_Position = u_projectionMatrix * u_viewMatrix * worldPosition;

    v_texture = texCoord;

    v_surfaceNormal = (u_transformationMatrix * vec4(normal, 0.0)).xyz;
    v_toLightVector = u_lightPosition - worldPosition.xyz;
}