/* Boxhead: Tamagotchi Clone
 *
 * Version 1:
 *    - He lives till the player closes the game.
 *    - Score is based off the time you keep Mr. Boxhead alive.
 *    - Night is a factor so every 10 hours you much interact with him.
 *          (8 hours roughly to sleep)
 *    - Feed, talk to, and play games with Mr. Boxhead.
 *    - If needs are not met in 24 hours then the rate of gaining a score goes
 *      down.
 *    - If multiplier is 0 then you lose.
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
        game.entertain();
    }

    // Input: Feed
    if (arduboy.justPressed(RIGHT_BUTTON)) {
        game.feed();
    }

    // Input: Hide/show the HUD
    if (arduboy.justPressed(DOWN_BUTTON)) {
        game.toggleHUD();
    }

    // Input: Talk
    if (arduboy.justPressed(LEFT_BUTTON)) {
        game.talkTo();
    }

    // Input: undefined
    if (arduboy.justPressed(A_BUTTON)) {
    }

    // Input: undefined
    if (arduboy.justPressed(B_BUTTON)) {
    }

    game.checkMultiplier();
    switch (game.getCurrentScreen()) {
        case Screen::GameOver:
            game.displayGameOver();
            break;
        case Screen::Home:
        default:
            game.displayHome();
            break;
    }

    arduboy.display(CLEAR_BUFFER);
}