#include "Game.h"

Game::Game()
{
}

bool Game::Initialize()
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
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
}
