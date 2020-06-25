#include "screentext.h"

#include <Arduboy2.h>

ScreenText::ScreenText(Arduboy2 arduboyObject, String entry)
    : text(entry), arduboy(arduboyObject) {
    update();
}

String ScreenText::getText() { return text; }
void ScreenText::setText(String newText) {
    text = newText;
    update();
}

void ScreenText::addToScreenBuffer(ScreenTextLocation location) {
    setTextToLocation(location);
    arduboy.print(text);
}
