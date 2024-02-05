#include "PhongGame.h"

PhongGame::PhongGame()
{
}

bool PhongGame::Initialize()
{
	// SDL 라이브러리 초기화, 초기화 하려는 모든 서브시스템의 비트 OR 연산값을 파라미터로 받음
	// 반환 정수값이 0이 아니면 초기화 실패했다는 의미
	// SDL_INIT_VIDEO : 윈도우 생성, OpenGL 관련 인터페이스 2D 그래픽스를 위한 비디오 서브시스템
	// SDL_INIT_AUDIO : 오디오 장치 관리, 재생 및 녹음
	// SDL_INIT_HAPTIC : 포스 피드백 이펙트 서브시스템
	// SDL_INIT_GAMECONTROLLER : 컨트롤러 입력 장치를 지원하는 서브시스템
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// 윈도우 제목, 윈도우가 배치될 x/y좌표(왼쪽 상단 기준), 너비와 높이, 윈도우 생성 관련 플래
	mWindow = SDL_CreateWindow(
		"SDL_OpenGL",				// 윈도우 제목
		100,						// 윈도우의 좌측 상단 x좌표
		100,						// 윈도우의 좌측 상단 y좌표
		1024,						// 윈도우의 너비
		768,						// 윈도우의 높이
		0);							// 윈도우 생성 관련 플래그 (0은 어떠한 플래그도 설정되지 않음을 의미)

	// 윈도우 생성 플래그
	// SDL_WINDOW_FULLSCREEN : 전체 화면 모드 사용
	// SDL_WINDOW_FULLSCREEN_DESKTOP : 현재 데스크톱의 해상도로 전체 화면 모드 사용, SDL_CreateWindow가 전달받는 너비/높이 파라미터는 무시
	// SDL_WINDOW_OPENGL : OpenGL 그래픽스 라이브러리에 대한 지원 추가
	// SDL_WINDOW_RESIZABLE : 윈도우 창 크기 조절 가능

	if (mWindow == nullptr)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// 두 번째 파라미터는 어떤 그래픽 카드를 사용할지를 지정
	// 게임이 여러 윈도우를 가진다면 의미가 있지만, 하나의 윈도우만 생성한다면 SDL이 그래픽 카드를 결정하라는 의미로 -1 기본값
	// 마지막은 초기화 플래그로 가속화된 렌더러(그래픽 하드웨어를 활용)의 사용 여부와 수직 동기화의 활성화 여부를 선택\
	// 이 두 플래그는 SDL_CreateRenderer의 유일한 플래그

	mRenderer = SDL_CreateRenderer(
		mWindow,					// 렌더링을 위해 생성한 윈도우
		-1,							// 일반적으로 -1
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
	// SDL은 OS로부터 받는 이벤트를 내부에 존재하는 큐(queue)로 관리
	// 이 큐는 입력 장치 뿐만 아니라 여러 유형의 윈도우 액션 이벤트를 포함

	// SDL_Event 포인터는 큐에서 막 제거된 이벤트에 관한 정보를 저장
	SDL_Event event;

	// 큐에 여전히 이벤트가 남아있는 동안
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// 이벤트가 SDL_QUIT이면 루프를 종료
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	
	// 키보드의 상태 얻기
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// 이스케이프 키를 눌렀다면 루프 종료
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	// W/S 키보드로 패들 위치 변경
	// 플레이어가 키를 동시에 눌렀을 때 mPaddleDir 값이 0임을 보장
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
	// 마지막 프레임 이후로 16ms가 경과할 때까지 대기
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// 델타 시간은 마지막 프레임 틱값과 현재 프레임 틱값의 차, 초 단위로 변환
	// 30 FPS로 진행되는 겜은 대략 한 프레임에서 다음 프레임까지 약 33ms 소요
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// 최대 델타 시간값으로 고정
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// 다음 프레임을 위해 틱값을 갱신
	mTicksCount = SDL_GetTicks();

	
	if (mPaddleDir != 0)
	{
		// 패들이 움직이고 있을 때, 화면 영역을 벗어나는지 검증
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
	// y차가 충분히 작고, 공비 올바른 x 값을 갖고 있고, 공이 왼쪽으로 이동하고 있다면
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
	// 기본 단계
	// 1. 푸면 버퍼를 단색으로 클리어
	// 2. 전체 게임 장면 렌더링
	// 3. 전면 버퍼와 후면 버퍼를 교환

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	// 후면 버퍼 지우기
	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_Rect wall{
		0,				// 왼쪽 상단 x
		0,				// 왼쪽 상단 y
		1024,			// 너비
		mThickness };	// 높이

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

	// 전면 버퍼와 후면 버퍼 교환
	SDL_RenderPresent(mRenderer);
}
