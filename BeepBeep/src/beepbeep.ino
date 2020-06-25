#include <Arduboy2.h>

Arduboy2 arduboy;

#include "screentext.h"

void setup() {
    arduboy.setFrameRate(30);
    arduboy.begin();
    arduboy.clear();
}

void loop() {
    if (!arduboy.nextFrame()) {
        return;
    }

    arduboy.pollButtons();

    // increase tone frequency
    if (arduboy.justPressed(UP_BUTTON)) {
    }
    // decrease tone frequency
    if (arduboy.justPressed(DOWN_BUTTON)) {
    }
    // change pin
    if (arduboy.justPressed(A_BUTTON)) {
    }
    // reset
    if (arduboy.justPressed(B_BUTTON)) {
    }

    arduboy.clear();
    ScreenText(arduboy, "Title").addToScreenBuffer(Center);
    arduboy.display();
}