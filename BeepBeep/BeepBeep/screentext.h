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

constexpr int character_width = 6;
constexpr int character_height = 8;

class ScreenText {
   private:
    Arduboy2 arduboy;

    int8_t x_min;
    int8_t x_max;
    int8_t x_center;
    int8_t y_min;
    int8_t y_max;
    int8_t y_center;
    int8_t len;
    String text;

    void update() {
        // title length in pixels
        len = text.length() * character_width;

        // axis minimums
        x_min = 0, y_min = 0;

        // axis maximums
        x_max = WIDTH - len, y_max = HEIGHT - character_height;

        // axis center
        x_center = (WIDTH - len) / 2,
        y_center = (HEIGHT - (character_height)) / 2;
    };

    void setTextToLocation(ScreenLocation location) {
        switch (location) {
            case ScreenLocation::TopLeft:
                arduboy.setCursor(x_min, y_min);
                break;
            case ScreenLocation::TopMiddle:
                arduboy.setCursor(x_center, y_min);
                break;
            case ScreenLocation::TopRight:
                arduboy.setCursor(x_max, y_min);
                break;
            case ScreenLocation::MiddleLeft:
                arduboy.setCursor(x_min, y_center);
                break;
            case ScreenLocation::Center:
                arduboy.setCursor(x_center, y_center);
                break;
            case ScreenLocation::MiddleRight:
                arduboy.setCursor(x_max, y_center);
                break;
            case ScreenLocation::BottomLeft:
                arduboy.setCursor(x_min, y_max);
                break;
            case ScreenLocation::BottomMiddle:
                arduboy.setCursor(x_center, y_max);
                break;
            case ScreenLocation::BottomRight:
                arduboy.setCursor(x_max, y_max);
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
