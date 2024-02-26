#pragma once
#include <glad/glad.h>

class EBO
{
public:
	GLuint ID;
	EBO(GLuint* vertices, GLsizeiptr size); // 바이트 단위의 크기에 사용하는 데이터타입(GLsizeiptr)

	void Bind();
	void UnBind();
	void Delete();
};