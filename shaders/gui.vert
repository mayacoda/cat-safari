#version 330

in vec2 position;

out vec2 v_textureCoords;

void main(void){

	gl_Position = vec4(position, 0.0, 1.0);
	v_textureCoords = vec2((position.x + 1.0) / 2.0, (position.y + 1.0) / 2.0);
}