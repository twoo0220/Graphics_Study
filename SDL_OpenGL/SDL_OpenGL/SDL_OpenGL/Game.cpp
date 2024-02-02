#include "Game.h"

Game::Game()
{
}

bool Game::Initialize()
{
	// SDL ���̺귯�� �ʱ�ȭ, �ʱ�ȭ �Ϸ��� ��� ����ý����� ��Ʈ OR ���갪�� �Ķ���ͷ� ����
	// ��ȯ �������� 0�� �ƴϸ� �ʱ�ȭ �����ߴٴ� �ǹ�
	// SDL_INIT_VIDEO : ������ ����, OpenGL ���� �������̽� 2D �׷��Ƚ��� ���� ���� ����ý���
	// SDL_INIT_AUDIO : ����� ��ġ ����, ��� �� ����
	// SDL_INIT_HAPTIC : ���� �ǵ�� ����Ʈ ����ý���
	// SDL_INIT_GAMECONTROLLER : ��Ʈ�ѷ� �Է� ��ġ�� �����ϴ� ����ý���
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// ������ ����, �����찡 ��ġ�� x/y��ǥ(���� ��� ����), �ʺ�� ����, ������ ���� ���� �÷�
	mWindow = SDL_CreateWindow(
		"SDL_OpenGL",				// ������ ����
		100,						// �������� ���� ��� x��ǥ
		100,						// �������� ���� ��� y��ǥ
		1024,						// �������� �ʺ�
		768,						// �������� ����
		0);							// ������ ���� ���� �÷��� (0�� ��� �÷��׵� �������� ������ �ǹ�)

	// ������ ���� �÷���
	// SDL_WINDOW_FULLSCREEN : ��ü ȭ�� ��� ���
	// SDL_WINDOW_FULLSCREEN_DESKTOP : ���� ����ũ���� �ػ󵵷� ��ü ȭ�� ��� ���, SDL_CreateWindow�� ���޹޴� �ʺ�/���� �Ķ���ʹ� ����
	// SDL_WINDOW_OPENGL : OpenGL �׷��Ƚ� ���̺귯���� ���� ���� �߰�
	// SDL_WINDOW_RESIZABLE : ������ â ũ�� ���� ����

	if (mWindow == nullptr)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::ProcessInput()
{
	// SDL�� OS�κ��� �޴� �̺�Ʈ�� ���ο� �����ϴ� ť(queue)�� ����
	// �� ť�� �Է� ��ġ �Ӹ� �ƴ϶� ���� ������ ������ �׼� �̺�Ʈ�� ����

	// SDL_Event �����ʹ� ť���� �� ���ŵ� �̺�Ʈ�� ���� ������ ����
	SDL_Event event;

	// ť�� ������ �̺�Ʈ�� �����ִ� ����
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// �̺�Ʈ�� SDL_QUIT�̸� ������ ����
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	
	// Ű������ ���� ���
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// �̽������� Ű�� �����ٸ� ���� ����
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
}
