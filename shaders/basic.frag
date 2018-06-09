#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 v_texture;
in vec3 v_surfaceNormal;
in vec3 v_toLightVector;

uniform vec4 u_color;
uniform sampler2D u_texture;
uniform vec3 u_lightColor;

void main() {
    vec3 unitNormal = normalize(v_surfaceNormal);
    vec3 unitLightVector = normalize(v_toLightVector);

    float nDotl = dot(unitNormal, unitLightVector);
    float brightness = max(nDotl, 0.0);

    vec3 diffuse = brightness * u_lightColor;


    out_color =  vec4(diffuse, 1.0) * texture(u_texture, v_texture);
}
