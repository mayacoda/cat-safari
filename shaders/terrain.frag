#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 v_texture;
in vec3 v_surfaceNormal;
in vec3 v_toLightVector;
in vec3 v_toCameraVector;
in float v_visibility;

uniform vec4 u_color;
uniform sampler2D u_texture;
uniform vec3 u_lightColor;
uniform vec3 u_skyColor;

uniform float u_shineDamper;
uniform float u_reflectivity;

void main() {
    vec3 unitNormal = normalize(v_surfaceNormal);
    vec3 unitLightVector = normalize(v_toLightVector);

    float nDotl = dot(unitNormal, unitLightVector);
    // ensure that no surface is ever black, simulating ambient lighting
    float brightness = max(nDotl, .3);

    // diffuse lighting
    vec3 diffuse = brightness * u_lightColor;

    // specular lighting
    vec3 unitCameraVector = normalize(v_toCameraVector);
    vec3 lightDirection = -unitLightVector;
    vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

    float specularFactor = dot(reflectedLightDirection, unitCameraVector);
    specularFactor = max(specularFactor, 0.0);

    float dampedFactor = pow(specularFactor, u_shineDamper);
    vec3 finalSpecular = dampedFactor * u_reflectivity * u_lightColor;

    out_color =  vec4(0, 0.1, 0, 1) + vec4(diffuse, 1.0) * texture(u_texture, v_texture) + vec4(finalSpecular, 1.0);
    out_color = mix(vec4(u_skyColor, 1.0), out_color, v_visibility);
}
