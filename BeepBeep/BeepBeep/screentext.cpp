#include "screentext.h"

#include <Arduboy2.h>

// Helps position text on screen to different bounds
ScreenText::ScreenText(Arduboy2 arduboyObject, String entry)
    : text(entry), arduboy(arduboyObject) {
    update();
}

// Returns text
String ScreenText::getText() { return text; }

// Setting new text will update the current min and max of cursor bounds
void ScreenText::setText(String newText) {
    text = newText;
    update();
}

// Sets the location where the cursor will be when printing the current text
void ScreenText::addToScreenBuffer(ScreenLocation location) {
    setTextToLocation(location);
    arduboy.print(text);
}
