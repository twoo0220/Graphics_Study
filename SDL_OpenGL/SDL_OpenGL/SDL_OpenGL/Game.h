#pragma once
#include "SDL.h"
#include "CommonType.h"

class Game
{
public:
	Game();
	
	bool Initialize();
	void RunLoop();
	void Shutdown();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

private:
	SDL_Window* mWindow = nullptr;
	SDL_Renderer* mRenderer = nullptr;

	bool mIsRunning = true;
	const int mThickness = 15;

	uint32_t mTicksCount = 0;
	int mPaddleDir = 0;
	float mPaddleH = 100.0f;
	Vector2 mPaddlePos{ 10.0f, 768.0f / 2.0f };
	Vector2 mBallPos{ 768.0f / 2.0f, 768.0f / 2.0f };
	Vector2 mBallVel{ -200.0f, 235.0f };
};
