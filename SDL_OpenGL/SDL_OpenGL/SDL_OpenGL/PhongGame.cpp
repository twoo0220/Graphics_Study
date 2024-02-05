#include "PhongGame.h"

PhongGame::PhongGame()
{
}

bool PhongGame::Initialize()
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

	// �� ��° �Ķ���ʹ� � �׷��� ī�带 ��������� ����
	// ������ ���� �����츦 �����ٸ� �ǹ̰� ������, �ϳ��� �����츸 �����Ѵٸ� SDL�� �׷��� ī�带 �����϶�� �ǹ̷� -1 �⺻��
	// �������� �ʱ�ȭ �÷��׷� ����ȭ�� ������(�׷��� �ϵ��� Ȱ��)�� ��� ���ο� ���� ����ȭ�� Ȱ��ȭ ���θ� ����\
	// �� �� �÷��״� SDL_CreateRenderer�� ������ �÷���

	mRenderer = SDL_CreateRenderer(
		mWindow,					// �������� ���� ������ ������
		-1,							// �Ϲ������� -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (mRenderer == nullptr)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	return true;
}

void PhongGame::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdatePhongGame();
		GenerateOutput();
	}
}

void PhongGame::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void PhongGame::ProcessInput()
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

	// W/S Ű����� �е� ��ġ ����
	// �÷��̾ Ű�� ���ÿ� ������ �� mPaddleDir ���� 0���� ����
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}

void PhongGame::UpdatePhongGame()
{
	// ������ ������ ���ķ� 16ms�� ����� ������ ���
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// ��Ÿ �ð��� ������ ������ ƽ���� ���� ������ ƽ���� ��, �� ������ ��ȯ
	// 30 FPS�� ����Ǵ� ���� �뷫 �� �����ӿ��� ���� �����ӱ��� �� 33ms �ҿ�
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// �ִ� ��Ÿ �ð������� ����
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// ���� �������� ���� ƽ���� ����
	mTicksCount = SDL_GetTicks();

	
	if (mPaddleDir != 0)
	{
		// �е��� �����̰� ���� ��, ȭ�� ������ ������� ����
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		if (mPaddlePos.y < (mPaddleH / 2.0f + mThickness))
		{
			mPaddlePos.y = mPaddleH / 2.0f + mThickness;
		}
		else if (mPaddlePos.y > (768.0f - mPaddleH / 2.0f - mThickness))
		{
			mPaddlePos.y = 768.0f - mPaddleH / 2.0f - mThickness;
		}
	}


	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	float diff = mPaddlePos.y - mBallPos.y;
	diff = (diff > 0.0f) ? diff : -diff;
	// y���� ����� �۰�, ���� �ùٸ� x ���� ���� �ְ�, ���� �������� �̵��ϰ� �ִٸ�
	if (diff <= mPaddleH / 2.0f && mBallPos.x <= 25.0f && mBallPos.x >= 20.0f && mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	else if (mBallPos.x <= 0.0f)
	{
		mIsRunning = false;
	}
	else if (mBallPos.x >= (1024.0f - mThickness) && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	if (mBallPos.y <= mThickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	else if (mBallPos.y >= (768 - mThickness) && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}
}

void PhongGame::GenerateOutput()
{
	// �⺻ �ܰ�
	// 1. Ǫ�� ���۸� �ܻ����� Ŭ����
	// 2. ��ü ���� ��� ������
	// 3. ���� ���ۿ� �ĸ� ���۸� ��ȯ

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	// �ĸ� ���� �����
	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_Rect wall{
		0,				// ���� ��� x
		0,				// ���� ��� y
		1024,			// �ʺ�
		mThickness };	// ����

	SDL_RenderFillRect(mRenderer, &wall);

	wall.y = 768 - mThickness;
	SDL_RenderFillRect(mRenderer, &wall);

	wall.x = 1024 - mThickness;
	wall.y = 0;
	wall.w = mThickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	SDL_Rect paddle{
	static_cast<int>(mPaddlePos.x),
	static_cast<int>(mPaddlePos.y - mPaddleH / 2),
	mThickness,
	static_cast<int>(mPaddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	SDL_Rect ball{
		static_cast<int>(mBallPos.x - mThickness / 2),
		static_cast<int>(mBallPos.y - mThickness / 2),
		mThickness,
		mThickness
	};

	SDL_RenderFillRect(mRenderer, &ball);

	// ���� ���ۿ� �ĸ� ���� ��ȯ
	SDL_RenderPresent(mRenderer);
}
