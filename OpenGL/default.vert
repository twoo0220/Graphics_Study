// Vertex Shader source code
#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;

// Colors
layout (location = 1) in vec3 aColor;

// Textures
layout (location = 2) in vec2 aTex;

// Outputs the color for the Fragment Shader
out vec3 color;
out vec2 texCoord;

// Controls the scale of the vertices
uniform float scale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	//gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	gl_Position = proj * view * model * vec4(aPos, 1.0);
	color = aColor;
	texCoord = aTex;
}


// Layouts help OpenGL read the Vertex Datait receives
// In this case, we say that on the 0th layout there is a vec3 datatype for positions
// Fragment Shader�� ������ ����ϴ� Shader�̱� ������ Vertex Shader�� ������ Fragment Shader�� ����ؾ� ��
// �׷��� �Ϸ��� color��� �̸��� vec3�� ����ϰ� main ���� ���� �迭���� ������ aColor�� �����ϰ� ����� ��
// Fragment shader���� vec3�� �Է����� ������ ��.

// uniform �� ������� �ʴ´ٸ� ���� �������� ����.
// OpenGL�� �������� �ڵ����� �����Ͽ� ������ �߻��� �� �ֱ� ����