/* September: A simple memory game where the more you play the faster it goes.
 *
 * Version 1:
 *      - Title Screen Image
 *      - Title Screen Ditty: September by Earth, Wind & Fire
 *      - Class: Game.h/Game.cpp
 */

#include <Arduboy2.h>

#include "assets.h"
#include "game.h"

Arduboy2 arduboy;

Game game = Game(arduboy);

constexpr int8_t frameRate = 60;
bool started;

void setup() {
    started = false;

    arduboy.begin();
    arduboy.setFrameRate(frameRate);
}

void loop() {
    if (!arduboy.nextFrame()) {
        return;
    }

    arduboy.pollButtons();

    // Input: undefined
    if (arduboy.justPressed(UP_BUTTON)) {
    }

    // Input: undefined
    if (arduboy.justPressed(RIGHT_BUTTON)) {
    }

    // Input: undefined
    if (arduboy.justPressed(DOWN_BUTTON)) {
    }

    // Input: undefined
    if (arduboy.justPressed(LEFT_BUTTON)) {
    }

    // Input: undefined
    if (arduboy.justPressed(A_BUTTON)) {
    }

    // Input: undefined
    if (arduboy.justPressed(B_BUTTON)) {
    }

    arduboy.display(CLEAR_BUFFER);

    if (!started) {
        arduboy.drawSlowXYBitmap(0, 0, titleScreen, WIDTH, HEIGHT, WHITE);
    }
}