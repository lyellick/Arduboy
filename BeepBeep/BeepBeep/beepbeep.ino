#include <Arduboy2.h>

Arduboy2 arduboy;

#include "screentext.h"

int8_t currentPin = 1;
String title = "BeepBeep";
String pinOneFrequencyBar = "";
String pinTwoFrequencyBar = "";
constexpr int8_t applicationFrameRate = 30;

void updateTextPointsToBuffer() {
    ScreenText(arduboy, title).addToScreenBuffer(ScreenLocation::TopMiddle);

    ScreenText(arduboy, "(" + String(currentPin) + ")")
        .addToScreenBuffer(ScreenLocation::TopRight);

    switch (currentPin) {
        case 1:
            ScreenText(arduboy, "[" + pinOneFrequencyBar + "]")
                .addToScreenBuffer(ScreenLocation::Center);

            ScreenText(arduboy, "Frequency: " +
                                    String(pinOneFrequencyBar.length() * 1000))
                .addToScreenBuffer(ScreenLocation::BottomLeft);
            break;
        case 2:
            ScreenText(arduboy, "[" + pinTwoFrequencyBar + "]")
                .addToScreenBuffer(ScreenLocation::Center);

            ScreenText(arduboy, "Frequency: " +
                                    String(pinTwoFrequencyBar.length() * 1000))
                .addToScreenBuffer(ScreenLocation::BottomLeft);
            break;
        default:
            break;
    }
}

void setup() {
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
        switch (currentPin) {
            case 1:
                if (String("[" + pinOneFrequencyBar + "]").length() !=
                    maxScreenWidth) {
                    pinOneFrequencyBar += "=";
                }
                break;
            case 2:
                if (String("[" + pinTwoFrequencyBar + "]").length() !=
                    maxScreenWidth) {
                    pinTwoFrequencyBar += "=";
                }
                break;
            default:
                break;
        }
    }

    // decrease tone frequency
    if (arduboy.justPressed(DOWN_BUTTON)) {
        String fullBar = "";
        switch (currentPin) {
            case 1:
                pinOneFrequencyBar = pinOneFrequencyBar.substring(
                    0, pinOneFrequencyBar.length() - 1);
                break;
            case 2:
                pinTwoFrequencyBar = pinTwoFrequencyBar.substring(
                    0, pinTwoFrequencyBar.length() - 1);
                break;
            default:
                break;
        }
    }

    // play beep
    if (arduboy.justPressed(A_BUTTON)) {
    }

    // change pin
    if (arduboy.justPressed(RIGHT_BUTTON)) {
        switch (currentPin) {
            case 1:
                ++currentPin;
                updateTextPointsToBuffer();
                break;
            case 2:
                --currentPin;
                updateTextPointsToBuffer();
                break;
            default:
                break;
        }
    }

    // undefined
    if (arduboy.justPressed(LEFT_BUTTON)) {
    }

    // reset
    if (arduboy.justPressed(B_BUTTON)) {
        switch (currentPin) {
            case 1:
                pinOneFrequencyBar = "";
                updateTextPointsToBuffer();
                break;
            case 2:
                pinTwoFrequencyBar = "";
                updateTextPointsToBuffer();
                break;
            default:
                break;
        }
    }

    updateTextPointsToBuffer();

    arduboy.display(CLEAR_BUFFER);
}