#include "pch.h"

#include "Game.h"

int main()
{
    std::cout << "Program Startsssssssssss!\n";

    Game* game = new Game();
    game->StartLoop();

    std::cout << "Program Ends!\n";
    return 0;
}
