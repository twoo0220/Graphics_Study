#pragma once

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	VAO();
	
	// Links a VBOto the VAO using a certain layout
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stribe, void* offset);
	void Bind();
	void Unbind();
	void Delete();

public:
	GLuint ID;	// ID reference for the Vertex Array Object
};