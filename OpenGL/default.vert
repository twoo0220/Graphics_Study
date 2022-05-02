// Vertex Shader source code
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform float scale;

void main()
{
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	color = aColor;
}


// Layouts help OpenGL read the Vertex Datait receives
// In this case, we say that on the 0th layout there is a vec3 datatype for positions
// Fragment Shader�� ������ ����ϴ� Shader�̱� ������ Vertex Shader�� ������ Fragment Shader�� ����ؾ� ��
// �׷��� �Ϸ��� color��� �̸��� vec3�� ����ϰ� main ���� ���� �迭���� ������ aColor�� �����ϰ� ����� ��
// Fragment shader���� vec3�� �Է����� ������ ��.

// uniform �� ������� �ʴ´ٸ� ���� �������� ����.
// OpenGL�� �������� �ڵ����� �����Ͽ� ������ �߻��� �� �ֱ� ����