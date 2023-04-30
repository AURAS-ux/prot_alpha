#include"Game.hpp"
#include "SETTINGS.hpp"

int main()
{
    Game* gameWindow = new Game(WIDTH, HEIGHT, BITSPERPIXEL,true);
    print_size();
    print_snooze_status();
    gameWindow->Update();
    gameWindow->~Game();
    return 0;
}