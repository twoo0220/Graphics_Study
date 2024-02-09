#include "Game.h"

Game::Game()
{
}

bool Game::Initialize()
{
	return false;
}

void Game::RunLoop()
{
}

void Game::Shutdown()
{
}

void Game::AddActor(Actor* actor)
{
}

void Game::RemoveActor(Actor* actor)
{
}

void Game::AddSprite(SpriteComponent* sprite)
{
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	return nullptr;
}

void Game::ProcessInput()
{
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
}

void Game::LoadData()
{
}

void Game::UnloadData()
{
}
