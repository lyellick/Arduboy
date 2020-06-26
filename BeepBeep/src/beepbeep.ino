#include <Arduboy2.h>

Arduboy2 arduboy;

#include "screentext.h"

constexpr int8_t applicationFrameRate = 30;

int8_t currentPin;

void setup() {
    currentPin = 1;

    arduboy.setFrameRate(applicationFrameRate);
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
        switch (currentPin) {
            case 1:
                ++currentPin;
                break;
            case 2:
                --currentPin;
                break;
            default:
                break;
        }
    }
    // reset
    if (arduboy.justPressed(B_BUTTON)) {
    }

    arduboy.clear();

    String title = "BeepBeep";
    ScreenText(arduboy, title).addToScreenBuffer(ScreenLocation::TopMiddle);

    String pin = "Pin: " + String(currentPin);
    ScreenText(arduboy, pin).addToScreenBuffer(ScreenLocation::BottomRight);
    arduboy.display();
}