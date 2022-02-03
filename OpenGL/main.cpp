#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// �Ϲ� �ε��Ҽ����� ����� ���� ������, opengl�� �ε��Ҽ����� �ٸ� ���� �����Ƿ� OpenGL ������ ����ϴ� ���� �� ������
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	// Lower left corner
	0.5, -0.5f * float(sqrt(3)) / 3, 0.0f,		// Lower righr corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,		// Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,// Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	// Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f		// Inner down
};

GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};


int main()
{
	// ��� OpenGL ��ü�� ������ ���� �׼�����
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 4.4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW we are using the CORE profile
	// So that means we only have the modren functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "OpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);

	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO vao1;
	vao1.Bind();

	VBO vbo1(vertices, sizeof(vertices));
	EBO ebo1(indices, sizeof(indices));

	vao1.LinkVBO(vbo1, 0);
	vao1.Unbind();
	vbo1.UnBind();
	ebo1.UnBind();

	// cpu�� gpu ���̿� ������ ������ �����Ƿ� ū ��ġ�� �Ѳ����� ����, �̰Ÿ� ���۶�� �θ��µ�
	// ���� ����, �ĸ� ���ۿ� �ٸ�
	// ���ε� - Ư�� ��ü�� ���� ��ü�� ����� �ش� ������ ��ü�� �����ϴ� �Լ��� ������ ������ ���� ��ü(���յ� ��ü)�� �����Ѵٴ� �ǹ�


	// EBO�� VAO�� ����ǹǷ� VAO ���ε��� ������ �Ŀ� ���ε��� �����ؾ� ��
	// VAO�� ���ε��� �����ϱ� ���� ���ε��� �����ϸ� ���������� VAO�� EBO�� ����ϴ� ���� ������ �ʴ´ٰ� OpenGL�� �˷��ֱ�


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();

		vao1.Bind();
		
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}