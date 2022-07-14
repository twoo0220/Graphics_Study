// Vertex Shader source code
#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;

// Colors
layout (location = 1) in vec3 aColor;

// Textures
layout (location = 2) in vec2 aTex;

layout (location = 3) in vec3 aNormal;

// Outputs the color for the Fragment Shader
out vec3 color;
out vec2 texCoord;

out vec3 Normal;
out vec3 crntPos;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	crntPos = vec3(model * vec4(aPos,1.0f));

	//gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	gl_Position = camMatrix * vec4(crntPos, 1.0);
	color = aColor;
	texCoord = aTex;

	Normal = aNormal;
}


// Layouts help OpenGL read the Vertex Datait receives
// In this case, we say that on the 0th layout there is a vec3 datatype for positions
// Fragment Shader�� ������ ����ϴ� Shader�̱� ������ Vertex Shader�� ������ Fragment Shader�� ����ؾ� ��
// �׷��� �Ϸ��� color��� �̸��� vec3�� ����ϰ� main ���� ���� �迭���� ������ aColor�� �����ϰ� ����� ��
// Fragment shader���� vec3�� �Է����� ������ ��.

// uniform �� ������� �ʴ´ٸ� ���� �������� ����.
// OpenGL�� �������� �ڵ����� �����Ͽ� ������ �߻��� �� �ֱ� ����