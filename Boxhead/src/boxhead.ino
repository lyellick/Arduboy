/* Boxhead: Tamagotchi Clone
 *
 * Version 1:
 *    - He lives till the player closes the game.
 *    - Score is based off the time you keep Mr. Boxhead alive.
 *    - Night is a factor so every 10 hours you much interact with him.
 *          (8 hours roughly to sleep)
 *    - Achievements per time period shown as  QR Code:
 *        - "First Second!" - You made it past the first second!
 *    =
 */

#include <Arduboy2.h>

#include "game.h"

Arduboy2 arduboy;

Game game = Game(arduboy);

Screen screen = Screen::Home;

constexpr int8_t frameRate = 60;

bool hideHUD = false;

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(frameRate);
}

void loop() {
    if (!arduboy.nextFrame()) {
        return;
    }

    game.trackTime();

    arduboy.pollButtons();

    // Input: undefined
    if (arduboy.justPressed(UP_BUTTON)) {
    }

    // Input: undefined
    if (arduboy.justPressed(RIGHT_BUTTON)) {
    }

    // Input: undefined
    if (arduboy.justPressed(DOWN_BUTTON)) {
        hideHUD = !hideHUD;
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

    switch (screen) {
        case Screen::Home:
        default:
            game.displayHome(hideHUD);
    }

    arduboy.display(CLEAR_BUFFER);
}