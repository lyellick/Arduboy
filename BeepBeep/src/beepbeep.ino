#include <Arduboy2.h>

Arduboy2 arduboy;

#include "screentext.h"

constexpr int8_t application_frame_rate = 30;

void setup() {
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
    }
    // reset
    if (arduboy.justPressed(B_BUTTON)) {
    }

    arduboy.clear();
    ScreenText(arduboy, "TL").addToScreenBuffer(ScreenLocation::TopLeft);
    ScreenText(arduboy, "TM").addToScreenBuffer(ScreenLocation::TopMiddle);
    ScreenText(arduboy, "TR").addToScreenBuffer(ScreenLocation::TopRight);
    ScreenText(arduboy, "ML").addToScreenBuffer(ScreenLocation::MiddleLeft);
    ScreenText(arduboy, "CTR").addToScreenBuffer(ScreenLocation::Center);
    ScreenText(arduboy, "MR").addToScreenBuffer(ScreenLocation::MiddleRight);
    ScreenText(arduboy, "BL").addToScreenBuffer(ScreenLocation::BottomLeft);
    ScreenText(arduboy, "BM").addToScreenBuffer(ScreenLocation::BottomMiddle);
    ScreenText(arduboy, "BR").addToScreenBuffer(ScreenLocation::BottomRight);
    arduboy.display();
}