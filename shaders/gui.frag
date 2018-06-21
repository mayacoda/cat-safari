#version 330

in vec2 v_textureCoords;

out vec4 out_Color;

uniform sampler2D u_guiTexture;

void main(void){

	out_Color = texture(u_guiTexture, v_textureCoords);

}