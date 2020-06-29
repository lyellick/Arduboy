#include "game.h"

#include <Arduboy2.h>

Game::Game(Arduboy2 arduboy) : arduboy(arduboy){};

void Game::trackTime() { incrementTimespan(); };

void Game::displayHome() {
    if (!hideHUD) {
        printStatus();
        printScore();
        printNeeds();
        printTimespan();
    }
};

void Game::displayGameOver() {
    int8_t statusLength = countChars(getStatus());
    int16_t endScore = static_cast<int16_t>(score);
    int16_t endScoreLength = countDigits(endScore);

    arduboy.setCursor((WIDTH - (9 * 6)) / 2, 18);
    arduboy.println(F("Game Over"));

    arduboy.setCursor((WIDTH - ((statusLength + 6) * 6)) / 2, 28);
    arduboy.print(F("Felt: "));
    arduboy.print(getStatus());

    arduboy.setCursor((WIDTH - (endScoreLength * 6)) / 2, 38);
    arduboy.println(endScore);
};
