#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

const unsigned int width = 800;
const unsigned int height = 800;

// �Ϲ� �ε��Ҽ����� ����� ���� ������, opengl�� �ε��Ҽ����� �ٸ� ���� �����Ƿ� OpenGL ������ ����ϴ� ���� �� ������
GLfloat vertices[] =
{ //	COORDINATES		 /			COLORS
	-0.5f, 0.0f, 0.5f,		0.83f,	0.3f,	0.02f, 	 0.0f, 0.0f, // Lower left corner
	-0.5f, 0.0f, -0.5f,		0.83f,	0.3f,	0.02f,	 5.0f, 0.0f,	// Lower righr corner
	 0.5f, 0.0f, -0.5f,		0.83f,	0.6f,	0.32f,	 0.0f, 0.0f,	// Upper corner
	 0.5f, 0.0f, 0.5f,		0.9f,	0.45f,	0.17f,	 5.0f, 0.0f,	// Inner left
	 0.0f, 0.8f, 0.0f,		0.9f,	0.45f,	0.17f,	 2.5f, 5.0f	// Inner left

};

GLuint indices[] =
{
	0, 1, 2, // Lower left triangle
	0, 2, 3, // Lower right triangle
	0, 1, 4, // Lower right triangle
	1, 2, 4, // Lower right triangle
	2, 3, 4, // Lower right triangle
	3, 0, 4 // Lower right triangle
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
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);

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
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

	VAO vao1;
	vao1.Bind();

	VBO vbo1(vertices, sizeof(vertices));	// Generates Vertex Buffer Object and links it to vertices
	EBO ebo1(indices, sizeof(indices));		// Generates Element Buffer Object and links it to indices

	// OpenGL���� �Լ� �ؼ��ϴ� ����� �˷���, glVertexAttribPointer
	//(ù��° ����) ���̾ƿ� ��ġ�� ������, ��ǥ/��ġ�� 0�̰� ������ 1
	//(�ι�° ����) ���̾ƿ��籸�� ��� ��(�� ��� ��� 3��-��ǥ3��, ���� 3��)
	//(����° ����) ���� ����� ����(GL_FLOAT)
	//(�׹�°) ��ǥ�� �Ÿ�(����)- �� ������ ���۰� �ٸ� ���� ������ �Ÿ�(����Ʈ), float ���� 6����ŭ�� �Ÿ��̹Ƿ� 6 * sizeof(float)
	//(�ټ���°) ������ - ����Ʈ ���� ���̾ƿ��� �ʱ� ������
	// ó�� 3�� ������Ұ� ��ǥ�̱� ������ ��ǥ�� ��� ���� �κ��� 0
	// ������ ��� ��ǥ 3�� ���������̱� ������ 3 * sizeof(float)

	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao1.LinkAttrib(vbo1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	vao1.Unbind();
	vbo1.UnBind();
	ebo1.UnBind();

	// cpu�� gpu ���̿� ������ ������ �����Ƿ� ū ��ġ�� �Ѳ����� ����, �̰Ÿ� ���۶�� �θ��µ�
	// ���� ����, �ĸ� ���ۿ� �ٸ�
	// ���ε� - Ư�� ��ü�� ���� ��ü�� ����� �ش� ������ ��ü�� �����ϴ� �Լ��� ������ ������ ���� ��ü(���յ� ��ü)�� �����Ѵٴ� �ǹ�


	// EBO�� VAO�� ����ǹǷ� VAO ���ε��� ������ �Ŀ� ���ε��� �����ؾ� ��
	// VAO�� ���ε��� �����ϱ� ���� ���ε��� �����ϸ� ���������� VAO�� EBO�� ����ϴ� ���� ������ �ʴ´ٰ� OpenGL�� �˷��ֱ�

	// Uniform �ٸ� ���̴����� �׼����� �� �ִ� ������ ���� ����, VAO�� ���� �ʰ�
	// uniform ���� �����Ϸ��� ���� �⺻ �Լ����� �������� �����;���

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		double curTime = glfwGetTime();
		if (curTime - prevTime >= (1 / 60))
		{
			rotation += 0.5f;
			prevTime = curTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


		glUniform1f(uniID, 0.5f); // ���̴�Ȱ��ȭ ���Ŀ� �����ؾ���
		popCat.Bind();

		vao1.Bind();
		
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	popCat.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}