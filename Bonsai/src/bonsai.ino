/* Bonsai: Growth Game
 *
 */

#include <Arduboy2.h>

#include "game.h"

Arduboy2 arduboy;

Game game = Game(arduboy);

constexpr int8_t frameRate = 60;

const uint8_t image[] PROGMEM = {
    0xFF, 0xC0, 0x80, 0x40, 0xB3, 0x40, 0x91, 0x40, 0x80, 0x40, 0x80,
    0x40, 0x81, 0x40, 0x9F, 0x40, 0x80, 0x40, 0xFF, 0xC0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

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

    arduboy.drawBitmap(0, 0, image, 10, 10, WHITE);
    arduboy.display(CLEAR_BUFFER);
}