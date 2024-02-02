#include <iostream>
#include "Game.h"

int SDL_main(int argc, char** argv)
{
    std::cout << "Hello World!\n";
    Game game;
    bool success = game.Initialize();
    if (success)
    {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
