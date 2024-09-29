#include "Renderer.h"

int main()
{
	Renderer game;
	if (game.initialize())
	{
		game.run();
	}
	
	return 0;
}