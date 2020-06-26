/*
Usage:
    ScreenText(arduboy, "TL").addToScreenBuffer(TopLeft);
    ScreenText(arduboy, "TM").addToScreenBuffer(TopMiddle);
    ScreenText(arduboy, "TR").addToScreenBuffer(TopRight);
    ScreenText(arduboy, "ML").addToScreenBuffer(MiddleLeft);
    ScreenText(arduboy, "CTR").addToScreenBuffer(Center);
    ScreenText(arduboy, "MR").addToScreenBuffer(MiddleRight);
    ScreenText(arduboy, "BL").addToScreenBuffer(BottomLeft);
    ScreenText(arduboy, "BM").addToScreenBuffer(BottomMiddle);
    ScreenText(arduboy, "BR").addToScreenBuffer(BottomRight);
*/

#include <Arduboy2.h>

constexpr int8_t maxScreenWidth = 21;

enum class ScreenLocation {
    TopLeft,
    TopMiddle,
    TopRight,
    MiddleLeft,
    Center,
    MiddleRight,
    BottomLeft,
    BottomMiddle,
    BottomRight,
    Default
};

constexpr int characterWidth = 6;
constexpr int characterHeight = 8;

class ScreenText {
   private:
    Arduboy2 arduboy;

    int8_t xMin;
    int8_t xMax;
    int8_t xCenter;
    int8_t yMin;
    int8_t yMax;
    int8_t yCenter;
    int8_t len;
    String text;

    void update() {
        // title length in pixels
        len = text.length() * characterWidth;

        // axis minimums
        xMin = 0, yMin = 0;

        // axis maximums
        xMax = WIDTH - len, yMax = HEIGHT - characterHeight;

        // axis center
        xCenter = (WIDTH - len) / 2, yCenter = (HEIGHT - (characterHeight)) / 2;
    };

    void setTextToLocation(ScreenLocation location) {
        switch (location) {
            case ScreenLocation::TopLeft:
                arduboy.setCursor(xMin, yMin);
                break;
            case ScreenLocation::TopMiddle:
                arduboy.setCursor(xCenter, yMin);
                break;
            case ScreenLocation::TopRight:
                arduboy.setCursor(xMax, yMin);
                break;
            case ScreenLocation::MiddleLeft:
                arduboy.setCursor(xMin, yCenter);
                break;
            case ScreenLocation::Center:
                arduboy.setCursor(xCenter, yCenter);
                break;
            case ScreenLocation::MiddleRight:
                arduboy.setCursor(xMax, yCenter);
                break;
            case ScreenLocation::BottomLeft:
                arduboy.setCursor(xMin, yMax);
                break;
            case ScreenLocation::BottomMiddle:
                arduboy.setCursor(xCenter, yMax);
                break;
            case ScreenLocation::BottomRight:
                arduboy.setCursor(xMax, yMax);
                break;
            default:
                break;
        }
    }

   public:
    ScreenText(Arduboy2 arduboy, String text);
    String getText();
    void setText(String newText);
    void addToScreenBuffer(ScreenLocation location);
};
