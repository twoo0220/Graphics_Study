#include <iostream>
#include "PhongGame.h"

int SDL_main(int argc, char** argv)
{
    std::cout << "Hello World!\n";
    PhongGame game;
    bool success = game.Initialize();
    if (success)
    {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
