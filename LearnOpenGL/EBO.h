#pragma once
#include <glad/glad.h>

class EBO
{
public:
	GLuint ID;
	EBO(GLuint* vertices, GLsizeiptr size); // ����Ʈ ������ ũ�⿡ ����ϴ� ������Ÿ��(GLsizeiptr)

	void Bind();
	void UnBind();
	void Delete();
};