/* Locomotion: Playing around with moving an entity around a bitmap.
 *
 * Version 1:
 *      - Kinda fun to play a chiptune version of The Locomotion by Little Eva
 *      - Layer One: background
 *      - Layer Two: train sprite
 */

#include <Arduboy2.h>

#include "game.h"
#include "sprites.h"

Arduboy2 arduboy;

Game game = Game(arduboy);

constexpr int8_t frameRate = 60;
int8_t x = 0;

void setup() {
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

    // Input: move right
    if (arduboy.justPressed(RIGHT_BUTTON)) {
        x = x + 4;
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

    arduboy.drawSlowXYBitmap(0, 0, background, WIDTH, HEIGHT, WHITE);
    if (x % 8 == 0) {
        arduboy.drawSlowXYBitmap(x, 25, locomotionPositionOne, 48, 32, WHITE);
    } else {
        arduboy.drawSlowXYBitmap(x, 25, locomotionPositionTwo, 48, 32, WHITE);
    }

    arduboy.display(CLEAR_BUFFER);
}