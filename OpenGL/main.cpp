#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


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

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// gpu가 소스코드를 이해할 수 없으므로 기계어로 컴파일
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// 이전에 만든 쉐이더가 프로그램 자체에 있으므로 기존꺼는 삭제
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 일반 부동소수점을 사용할 수도 있지만, opengl의 부동소수점은 다를 수도 있으므로 OpenGL 버전을 사용하는 것이 더 안전함
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

	// cpu와 gpu 사이에 데이터 전달은 느리므로 큰 배치에 한꺼번에 전달, 이거를 버퍼라고 부르는데
	// 전면 버퍼, 후면 버퍼와 다름
	// 바인딩 - 특정 개체를 현재 개체로 만들고 해당 유형의 개체를 수정하는 함수를 실행할 때마다 현재 개체(결합된 개체)를 수정한다는 의미
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// EBO는 VAO에 저장되므로 VAO 바인드을 해제한 후에 바인딩을 해제해야 함
	// VAO의 바인등을 해제하기 전에 바인등을 해제하면 본질적으로 VAO가 EBO를 사용하는 것을 원하지 않는다고 OpenGL에 알려주기
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Specify the color of the backgroun
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}