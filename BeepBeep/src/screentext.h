#include <Arduboy2.h>

enum ScreenTextLocation {
    TopLeft,
    TopRight,
    MiddleLeft,
    MiddleRight,
    BottomLeft,
    BottomRight,
    Center,
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
            case Center:
                arduboy.setCursor(x_center, y_center);
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
