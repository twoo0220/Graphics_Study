#version 330 core

in vec4 vertexPos;
uniform float uTheta; // rotation angle: uniform

void main(void) {
	gl_Position.x = vertexPos.x * cos(uTheta) - vertexPos.y * sin(uTheta);
	gl_Position.y = vertexPos.x * sin(uTheta) + vertexPos.y * cos(uTheta);
	gl_Position.zw = vertexPos.zw;
}
