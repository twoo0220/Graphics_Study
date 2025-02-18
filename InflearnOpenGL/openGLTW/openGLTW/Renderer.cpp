#include "Renderer.h"
#include "glm/glm.hpp"

float Renderer::mColor[4] = { 0.0f, 0.0f,0.0f, 1.0f };

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	unsigned int renderObjectSize = static_cast<unsigned int>(mRenderObject.size());
	for (unsigned int i = 0; i < renderObjectSize; ++i)
	{
		if (nullptr != mRenderObject[i])
		{
			mRenderObject[i]->deinitialize();
		}
	}

	mRenderObject.clear();
	glfwTerminate();
}

bool Renderer::initialize()
{
	if (!glfwInit())
	{
		std::cerr << "glfwInit failed\n";
		return false;
	}

	mWindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (mWindow == nullptr)
	{
		glfwTerminate();
		std::cerr << "glfwCreateWindow failed\n";
		return false;
	}

	glfwMakeContextCurrent(mWindow);

	// Must be used after glfwMakeContextCurrent()
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "glewInit failed : " << glewGetErrorString(err) << "\n";
		return false;
	}

	glfwSetWindowRefreshCallback(mWindow, refreshFunc);
	glfwSetKeyCallback(mWindow, keyFunc);

	return true;
}

void Renderer::run()
{
	mRenderObject.push_back(std::make_shared<Triangle>());
	mRenderObject.push_back(std::make_shared<tangled>());

	unsigned int renderObjectSize = static_cast<unsigned int>(mRenderObject.size());

	for (unsigned int i = 0; i < renderObjectSize; ++i)
	{
		mRenderObject[i]->initialize();
	}
	while (!glfwWindowShouldClose(mWindow))
	{
		glEnable(GL_DEPTH_TEST);
		glDepthRange(-1.0f, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (unsigned int i = 0; i < renderObjectSize; ++i)
		{
			mRenderObject[i]->update();
		}

		glFinish();

		calculateFPS();
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}

void Renderer::calculateFPS()
{
	static unsigned int frameCount = 0;
	static std::chrono::time_point<std::chrono::high_resolution_clock> prevTime = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::high_resolution_clock> currentTime = std::chrono::high_resolution_clock::now();

	if ((currentTime - prevTime) >= std::chrono::seconds(1))
	{
		std::cout << "FPS : " << frameCount << "\n";
		frameCount = 0;
		prevTime = currentTime;
	}
	else
	{
		++frameCount;
	}
}

void Renderer::refreshFunc(GLFWwindow* window)
{
	//std::cout << "Refresh CallBack!\n";
	// refresh
	glClear(GL_COLOR_BUFFER_BIT);
	glFinish();

	// GLFW action
	glfwSwapBuffers(window);
}

void Renderer::keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
	{
		if (action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		break;
	}
	case GLFW_KEY_1: 
	{
		mColor[0] += 0.01f;
		if (mColor[0] > 1.0f)
		{
			mColor[0] = 0.0f;
		}
		glClearColor(mColor[0], mColor[1], mColor[2], mColor[3]);
		break;
	}
	case GLFW_KEY_2:
	{
		mColor[1] += 0.01f;
		if (mColor[1] > 1.0f)
		{
			mColor[1] = 0.0f;
		}
		glClearColor(mColor[0], mColor[1], mColor[2], mColor[3]);
		break;
	}
	case GLFW_KEY_3:
	{
		mColor[2] += 0.01f;
		if (mColor[2] > 1.0f)
		{
			mColor[2] = 0.0f;
		}
		glClearColor(mColor[0], mColor[1], mColor[2], mColor[3]);
		break;
	}
	case GLFW_KEY_C:
	{
		static bool VSyncOn = true;
		if ((mods == (GLFW_MOD_SHIFT | GLFW_MOD_CONTROL)) && (action == GLFW_PRESS))
		{
			if (VSyncOn)
			{
				glfwSwapInterval(0); // V-Sync off
				VSyncOn = false;
			}
			else
			{
				glfwSwapInterval(1); // V-Sync on
				VSyncOn = true;
			}
		}
		break;
	}
	default:
	{
		break;
	}
	}
}
