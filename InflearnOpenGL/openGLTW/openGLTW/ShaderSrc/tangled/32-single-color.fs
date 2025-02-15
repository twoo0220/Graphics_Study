#version 330 core

uniform vec4 tangledColor; // uniform color: uniform
out vec4 tanColor; // fragment color: framebuffer

void main(void) {
	tanColor = tangledColor;
}
