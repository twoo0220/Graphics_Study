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

// 일반 부동소수점을 사용할 수도 있지만, opengl의 부동소수점은 다를 수도 있으므로 OpenGL 버전을 사용하는 것이 더 안전함
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
	// 모든 OpenGL 개체는 참조에 의해 액세스됨
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

	// OpenGL에게 함수 해석하는 방법을 알려줌, glVertexAttribPointer
	//(첫번째 변수) 레이아웃 위치를 지정함, 좌표/위치는 0이고 색상은 1
	//(두번째 변수) 레이아웃당구성 요소 수(두 경우 모두 3개-좌표3개, 색상 3개)
	//(세번째 변수) 구성 요소의 유형(GL_FLOAT)
	//(네번째) 좌표의 거리(보폭)- 한 정점의 시작과 다른 정점 사이의 거리(바이트), float 형식 6개만큼의 거리이므로 6 * sizeof(float)
	//(다섯번째) 오프셋 - 바이트 단위 레이아웃의 초기 오프셋
	// 처음 3개 구성요소가 좌표이기 때문에 좌표의 경우 시작 부분은 0
	// 색상의 경우 좌표 3개 다음부터이기 때문에 3 * sizeof(float)

	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao1.LinkAttrib(vbo1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	vao1.Unbind();
	vbo1.UnBind();
	ebo1.UnBind();

	// cpu와 gpu 사이에 데이터 전달은 느리므로 큰 배치에 한꺼번에 전달, 이거를 버퍼라고 부르는데
	// 전면 버퍼, 후면 버퍼와 다름
	// 바인딩 - 특정 개체를 현재 개체로 만들고 해당 유형의 개체를 수정하는 함수를 실행할 때마다 현재 개체(결합된 개체)를 수정한다는 의미


	// EBO는 VAO에 저장되므로 VAO 바인드을 해제한 후에 바인딩을 해제해야 함
	// VAO의 바인등을 해제하기 전에 바인등을 해제하면 본질적으로 VAO가 EBO를 사용하는 것을 원하지 않는다고 OpenGL에 알려주기

	// Uniform 다른 쉐이더에서 액세스할 수 있는 일종의 범용 변수, VAO를 쓰지 않고도
	// uniform 값을 지정하려면 먼저 기본 함수에서 참조값을 가져와야함

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


		glUniform1f(uniID, 0.5f); // 쉐이더활성화 이후에 실행해야함
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