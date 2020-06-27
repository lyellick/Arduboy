/* Boxhead: Tamagotchi Clone
 *
 * Version 1:
 *    - He lives till the player closes the game.
 *    - Score is based off the time you keep Mr. Boxhead alive.
 *    - Achievements per time period shown as  QR Code:
 *        - "First Second!" - You made it past the first second!
 *    =
 */

#include <Arduboy2.h>
#include <score.h>

Arduboy2 arduboy;
Score score;

void setup() {
    score = Score();
    arduboy.begin();
    arduboy.setFrameRate(60);
}

void loop() {
    if (!arduboy.nextFrame()) {
        return;
    }

    score.trackGameTime();

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

    arduboy.setCursor(0, 0);
    arduboy.print(F("Seconds:    "));
    arduboy.println(score.seconds);
    arduboy.print(F("Minutes:    "));
    arduboy.println(score.minutes);
    arduboy.print(F("Hours:      "));
    arduboy.println(score.hours);
    arduboy.print(F("Days:       "));
    arduboy.println(score.days);
    arduboy.print(F("Years:      "));
    arduboy.println(score.years);
    arduboy.print(F("Score:      "));
    arduboy.println(score.getScore(), 3);
    arduboy.print(F("Multiplier: "));
    arduboy.println(score.getMultiplier(), 3);
    arduboy.display(CLEAR_BUFFER);
}