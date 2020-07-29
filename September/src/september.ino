/* September: A simple memory game where the more you play the faster it goes.
 *
 * Version 1:
 *      - Title Screen Image
 *      - Title Screen Ditty: September by Earth, Wind & Fire
 *      - Class: Game.h/Game.cpp
 */

#include <Arduboy2.h>

#include "game.h"

Arduboy2 arduboy;

constexpr int8_t frameRate = 60;
constexpr int8_t sequenceLength = 5;

Game game = Game(arduboy, sequenceLength);

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(frameRate);
    arduboy.initRandomSeed();
    game.initialize();
}

void loop() {
    if (!arduboy.nextFrame()) {
        return;
    }

    arduboy.pollButtons();

    int16_t button = arduboy.buttonsState();

    arduboy.display(CLEAR_BUFFER);

    switch (game.getCurrentScreen()) {
        case Screen::Title:
            game.displayTitle(arduboy.justPressed(button));
            break;
        case Screen::Board:
            game.displayBoard(button);
            break;
        case Screen::Win:
            game.displayWinScreen(arduboy.justPressed(button));
            break;
        case Screen::Loose:
            game.displayLooseScreen(arduboy.justPressed(button));
            break;
        default:
            break;
    }
}