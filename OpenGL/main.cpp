#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
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

GLfloat lightVertices[] =
{
	-0.1f, -0.1f, 0.1f,
	-0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, 0.1f,
	-0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, 0.1f,
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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

	Shader lightShader("light.vert", "light.frag");
	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	lightVAO.Unbind();
	lightVBO.UnBind();
	lightEBO.UnBind();

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));


	// Texture
	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);



		shaderProgram.Activate();
		camera.Matrix(shaderProgram, "camMatrix");

		popCat.Bind();

		vao1.Bind();
		
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


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