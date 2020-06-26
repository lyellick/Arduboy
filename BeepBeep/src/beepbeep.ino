/* Beeps at different frequencies depending on what store you are one and what
 * value.
 */

#include <Arduboy2.h>
#include <Arduboy2Beep.h>

Arduboy2 arduboy;
BeepPin2 beep;

#include "screentext.h"

int8_t currentBeepStore = 1;
String title = "BeepBeep";
String beepStoreOne = "";
String beepStoreTwo = "";
constexpr int8_t applicationFrameRate = 50;

void updateTextPointsToBuffer() {
    ScreenText(arduboy, title).addToScreenBuffer(ScreenLocation::TopMiddle);

    // Pin: <pin>
    ScreenText(arduboy, "Store: " + String(currentBeepStore))
        .addToScreenBuffer(ScreenLocation::BottomRight);

    switch (currentBeepStore) {
        case 1:
            ScreenText(arduboy, "[" + beepStoreOne + "]")
                .addToScreenBuffer(ScreenLocation::Center);

            ScreenText(arduboy,
                       // Freq: <frequency>
                       "Freq: " + String(beepStoreOne.length() * 150))
                .addToScreenBuffer(ScreenLocation::BottomLeft);
            break;
        case 2:
            ScreenText(arduboy, "[" + beepStoreTwo + "]")
                .addToScreenBuffer(ScreenLocation::Center);

            ScreenText(arduboy,
                       // Freq: <frequency>
                       "Freq: " + String(beepStoreTwo.length() * 150))
                .addToScreenBuffer(ScreenLocation::BottomLeft);
            break;
        default:
            break;
    }
}

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(applicationFrameRate);

    beep.begin();
}

void loop() {
    if (!arduboy.nextFrame()) {
        return;
    }

    beep.timer();

    arduboy.pollButtons();

    // increase tone frequency
    if (arduboy.justPressed(UP_BUTTON)) {
        switch (currentBeepStore) {
            case 1:
                if (String("[" + beepStoreOne + "]").length() !=
                    maxScreenWidth) {
                    beepStoreOne += "=";
                }
                break;
            case 2:
                if (String("[" + beepStoreTwo + "]").length() !=
                    maxScreenWidth) {
                    beepStoreTwo += "=";
                }
                break;
            default:
                break;
        }
    }

    // decrease tone frequency
    if (arduboy.justPressed(DOWN_BUTTON)) {
        switch (currentBeepStore) {
            case 1:
                beepStoreOne =
                    beepStoreOne.substring(0, beepStoreOne.length() - 1);
                break;
            case 2:
                beepStoreTwo =
                    beepStoreTwo.substring(0, beepStoreTwo.length() - 1);
                break;
            default:
                break;
        }
    }

    // play beep
    if (arduboy.justPressed(A_BUTTON)) {
        if (beepStoreOne.length() != 0 || beepStoreTwo.length() != 0) {
            switch (currentBeepStore) {
                case 1:
                    beep.tone(beep.freq(beepStoreOne.length() * 150), 15);
                    break;
                case 2:
                    beep.tone(beep.freq(beepStoreTwo.length() * 150), 15);
                    break;
                default:
                    break;
            }
        }
    }

    // change pin
    if (arduboy.justPressed(RIGHT_BUTTON)) {
        beep.noTone();
        switch (currentBeepStore) {
            case 1:
                currentBeepStore = 2;
                updateTextPointsToBuffer();
                break;
            case 2:
                currentBeepStore = 1;
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
        beep.noTone();
        switch (currentBeepStore) {
            case 1:
                beepStoreOne = "";
                updateTextPointsToBuffer();
                break;
            case 2:
                beepStoreTwo = "";
                updateTextPointsToBuffer();
                break;
            default:
                break;
        }
    }

    updateTextPointsToBuffer();

    arduboy.display(CLEAR_BUFFER);
}