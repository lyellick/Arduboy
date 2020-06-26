#include <Arduboy2.h>

Arduboy2 arduboy;

#include "screentext.h"

constexpr int8_t application_frame_rate = 30;

int8_t current_pin;

void setup() {
    current_pin = 1;

    arduboy.setFrameRate(application_frame_rate);
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
        switch (current_pin) {
            case 1:
                ++current_pin;
                break;
            case 2:
                --current_pin;
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

    String pin = "Pin: " + String(current_pin);
    ScreenText(arduboy, pin).addToScreenBuffer(ScreenLocation::BottomRight);
    arduboy.display();
}