#version 330 core

in vec4 aPos; // vertex position: attribute
in vec4 aColor;
out vec4 vColor;
uniform mat4 uMat;

void main(void) {
	gl_Position = uMat * aPos; // transformation
	gl_Position.z *= -1.0f;
	vColor = aColor;
}
