#include "game.h"

#include <Arduboy2.h>

#include "assets.h"

Game::Game(Arduboy2& arduboy, int8_t sequenceLength)
    : arduboy(arduboy), sequenceLength(sequenceLength) {
    sequence = new int16_t[sequenceLength];
};

void Game::displayTitle(bool anyKeyPressed) {
    if (anyKeyPressed) {
        screen = Screen::Board;
    } else {
        arduboy.drawSlowXYBitmap(0, 0, titleScreen, WIDTH, HEIGHT, WHITE);
    }
};

void Game::displayBoard(int16_t button) { validateInputInSequence(button); };

void Game::displayLooseScreen(bool anyKeyPressed) {
    if (anyKeyPressed) {
        resetGame();
    } else {
        arduboy.setCursor((WIDTH - (9 * 6)) / 2, 18);
        arduboy.println(F("Game Over"));
        arduboy.setCursor(4, 28);
        arduboy.print(F("You Remembered Up To"));
        arduboy.setCursor(32, 38);
        arduboy.print(sequenceIndex);
        arduboy.print(F(" Sequences"));
    }
};

void Game::displayWinScreen(bool anyKeyPressed) {
    if (anyKeyPressed) {
        resetGame();
    } else {
        arduboy.setCursor((WIDTH - (9 * 6)) / 2, 18);
        arduboy.println(F("You Win!"));
        arduboy.setCursor(8, 28);
        arduboy.print(F("You Remembered All"));
        arduboy.setCursor(29, 38);
        arduboy.print(sequenceIndex);
        arduboy.print(F(" Sequences"));
    }
};

void Game::initialize() { generateSequence(); };