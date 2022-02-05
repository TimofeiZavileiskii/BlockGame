#include "pch.h"

#include <iostream>
#include "Game.h"

int main()
{
    std::cout << "Program Starts!\n";

    Game* game = new Game();
    game->StartLoop();

    std::cout << "Program Ends!\n";
    return 0;
}
