/* Boxhead: Tamagotchi Clone
 *
 * Version 1:
 *    - He lives till the player closes the game.
 *    - Score is based off the time you keep Mr. Boxhead alive.
 *    -
 */

#include <Arduboy2.h>

Arduboy2 arduboy;

int8_t frames = 0;
int8_t milliseconds = 0;
int8_t seconds = 0;
int8_t minutes = 0;
int8_t hours = 0;
int16_t days = 0;
int32_t years = 0;

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(60);
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

    ++frames;
    if (frames == 60) {
        frames = 0;
        ++seconds;
        if (seconds == 60) {
            seconds = 0;
            ++minutes;
            if (minutes == 60) {
                minutes = 0;
                ++hours;
                if (hours == 24) {
                    hours = 0;
                    ++days;
                    if (days == 365) {
                        days = 0;
                        ++years;
                    }
                }
            }
        }
    }

    arduboy.setCursor(0, 0);
    arduboy.print(F("Seconds: "));
    arduboy.println(seconds);
    arduboy.print(F("Minutes: "));
    arduboy.println(minutes);
    arduboy.print(F("Hours: "));
    arduboy.println(hours);
    arduboy.print(F("Days: "));
    arduboy.println(days);
    arduboy.print(F("Years: "));
    arduboy.println(years);
    arduboy.display(CLEAR_BUFFER);
}