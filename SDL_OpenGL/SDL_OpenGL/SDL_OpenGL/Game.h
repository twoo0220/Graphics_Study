#pragma once
#include "SDL.h"

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
	bool mIsRunning = true;
};
