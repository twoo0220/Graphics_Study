// Fragment Shader source code
#version 330 core
out vec4 FragColor;

// Inputs the color from the Vertex Shader
in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
	FragColor = texture(tex0, texCoord);
}
//FragColor = vec4(color, 1.0f);