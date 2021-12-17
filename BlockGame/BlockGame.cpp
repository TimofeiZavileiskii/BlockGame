#include "pch.h"

#include <iostream>
#include "Game.h"

int main()
{
    std::cout << "Hello World!\n";

    Game* game = new Game();
    game->StartLoop();

    std::cout << "Program Ends!\n";
    return 0;
}
