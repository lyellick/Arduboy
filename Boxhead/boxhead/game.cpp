#include "game.h"

#include <Arduboy2.h>

Game::Game(Arduboy2 arduboy) : arduboy(arduboy){};

void Game::trackTime() { incrementTimespan(); };

void Game::displayHome() {
    printScore();
    printTimespan();
};
