#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 v_texture;
out vec3 v_surfaceNormal;
out vec3 v_toLightVector;
out vec3 v_toCameraVector;
out float v_visibility;

uniform mat4 u_transformationMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform vec3 u_lightPosition;

const float density = 0.0035;
const float gradient = 2;

void main() {

    vec4 worldPosition = u_transformationMatrix * position;
    vec4 positionRelativeToCam = u_viewMatrix * worldPosition;

    gl_Position = u_projectionMatrix * positionRelativeToCam;

    v_texture = texCoord;

    // diffused lighting
    v_surfaceNormal = (u_transformationMatrix * vec4(normal, 0.0)).xyz;
    v_toLightVector = u_lightPosition - worldPosition.xyz;

    // fog
    float distance = length(positionRelativeToCam.xyz);
    v_visibility = clamp(exp(-pow((distance * density), gradient)), 0, 1);

    //specular lighting
    v_toCameraVector = (inverse(u_viewMatrix) * vec4(0, 0, 0, 0)).xyz - worldPosition.xyz;
}