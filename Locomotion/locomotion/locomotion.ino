/* Locomotion
 *
 * Playing around with moving an entity around a bitmap.
 */

#include <Arduboy2.h>

#include "game.h"

Arduboy2 arduboy;

Game game = Game(arduboy);

constexpr int8_t frameRate = 60;

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
}