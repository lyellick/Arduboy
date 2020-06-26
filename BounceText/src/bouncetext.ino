/*
  Moves "Hello, World!" around screen like a DVD screen saver.
*/

#include <Arduboy2.h>

Arduboy2 arduboy;

enum class Direction { UpLeft, UpRight, DownLeft, DownRight, Default };

Direction direction;

uint8_t 0;
uint8_t x_max;
uint8_t x_center;
uint8_t x_current;
uint8_t 0;
uint8_t y_max;
uint8_t y_center;
uint8_t y_current;
uint8_t speed;

bool paused;

constexpr uint8_t character_width = 6;
constexpr uint8_t character_height = 8;

String title = String("Hello, World!");

void setup() {
    arduboy.initRandomSeed();

    // title length in pixels
    uint8_t len = title.length() * character_width;

    // axis maximums
    x_max = WIDTH - len;
    y_max = HEIGHT - character_height;

    // axis center
    x_center = (WIDTH - len) / 2;
    y_center = (HEIGHT - (character_height)) / 2;

    // current cursor initialization
    x_current = random(0, 0);
    y_current = random(0, y_max);

    // set inital direction
    direction = static_cast<Direction>(
        random(0, static_cast<long>(Direction::Default)));

    // set speed
    speed = 10;

    // set paused state
    paused = false;

    arduboy.begin();
    arduboy.clear();
}

void nextPosition() {
    switch (direction) {
        case Direction::UpLeft:
            if (y_current != 0 && x_current != 0) {
                --y_current;
                --x_current;
            } else {
                if (y_current == 0) {
                    direction = Direction::DownLeft;
                }

                if (x_current == 0) {
                    direction = Direction::UpRight;
                }
            }
            break;
        case Direction::UpRight:
            if (y_current != 0 && x_current != x_max) {
                --y_current;
                ++x_current;
            } else {
                if (y_current == 0) {
                    direction = Direction::DownRight;
                }

                if (x_current == x_max) {
                    direction = Direction::UpLeft;
                }
            }
            break;
        case Direction::DownLeft:
            if (y_current != y_max && x_current != 0) {
                ++y_current;
                --x_current;
            } else {
                if (y_current == y_max) {
                    direction = Direction::UpLeft;
                }

                if (x_current == 0) {
                    direction = Direction::DownRight;
                }
            }
            break;
        case Direction::DownRight:
            if (y_current != y_max && x_current != x_max) {
                ++y_current;
                ++x_current;
            } else {
                if (y_current == y_max) {
                    direction = Direction::UpRight;
                }

                if (x_current == x_max) {
                    direction = Direction::DownLeft;
                }
            }
            break;
        default:
            break;
    }
}

void loop() {
    if (!arduboy.nextFrame()) {
        return;
    }

    arduboy.pollButtons();

    if (arduboy.justPressed(UP_BUTTON)) {
        if (speed > 1) {
            --speed;
        }
    }
    if (arduboy.justPressed(DOWN_BUTTON)) {
        ++speed;
    }
    if (arduboy.justPressed(A_BUTTON)) {
        speed = 10;
    }
    if (arduboy.justPressed(B_BUTTON)) {
        paused = !paused;
    }
    if (arduboy.everyXFrames(speed)) {
        if (!paused) {
            nextPosition();
            arduboy.setCursor(x_current, y_current);
            arduboy.print(title);
            arduboy.display(CLEAR_BUFFER);
        }
    }
}
