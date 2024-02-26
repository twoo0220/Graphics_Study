#pragma once
#include <glad/glad.h>

class VBO
{
public:
	GLuint ID;
	VBO(GLfloat* vertices, GLsizeiptr size); // 바이트 단위의 크기에 사용하는 데이터타입(GLsizeiptr)

	void Bind();
	void UnBind();
	void Delete();
};