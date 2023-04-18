#include"Game.hpp"
#include "SETTINGS.hpp"

int main()
{
    Game* gameWindow = new Game(WIDTH, HEIGHT, BITSPERPIXEL,true);
    print_size();
    gameWindow->Update();
    gameWindow->~Game();
    return 0;
}