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

enum ScreenTextLocation {
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

class ScreenText {
   private:
    Arduboy2 arduboy;
    const int CHAR_WIDTH = 6, CHAR_HEIGHT = 8;
    int x_min, x_max, x_center, y_min, y_max, y_center, len;
    String text;

    void update() {
        // title length in pixels
        len = text.length() * CHAR_WIDTH;

        // axis minimums
        x_min = 0, y_min = 0;

        // axis maximums
        x_max = WIDTH - len, y_max = HEIGHT - CHAR_HEIGHT;

        // axis center
        x_center = (WIDTH - len) / 2, y_center = (HEIGHT - (CHAR_HEIGHT)) / 2;
    };

    void setTextToLocation(ScreenTextLocation location) {
        switch (location) {
            case TopLeft:
                arduboy.setCursor(x_min, y_min);
                break;
            case TopMiddle:
                arduboy.setCursor(x_center, y_min);
                break;
            case TopRight:
                arduboy.setCursor(x_max, y_min);
                break;
            case MiddleLeft:
                arduboy.setCursor(x_min, y_center);
                break;
            case Center:
                arduboy.setCursor(x_center, y_center);
                break;
            case MiddleRight:
                arduboy.setCursor(x_max, y_center);
                break;
            case BottomLeft:
                arduboy.setCursor(x_min, y_max);
                break;
            case BottomMiddle:
                arduboy.setCursor(x_center, y_max);
                break;
            case BottomRight:
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
    void addToScreenBuffer(ScreenTextLocation location);
};
