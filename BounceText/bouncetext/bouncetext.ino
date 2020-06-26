/*
  Moves "Hello, World!" around screen like a DVD screen saver.
*/

#include <Arduboy2.h>

Arduboy2 arduboy;

enum class Direction { UpLeft, UpRight, DownLeft, DownRight, Default };

Direction direction;

uint8_t xMax;
uint8_t xCenter;
uint8_t xCurrent;
uint8_t yMax;
uint8_t yCenter;
uint8_t yCurrent;
uint8_t speed;

bool paused;

constexpr uint8_t characterwidth = 6;
constexpr uint8_t characterHeight = 8;

String title = String("Hello, World!");

void setup() {
    arduboy.initRandomSeed();

    // title length in pixels
    uint8_t len = title.length() * characterwidth;

    // axis maximums
    xMax = WIDTH - len;
    yMax = HEIGHT - characterHeight;

    // axis center
    xCenter = (WIDTH - len) / 2;
    yCenter = (HEIGHT - (characterHeight)) / 2;

    // current cursor initialization
    xCurrent = random(0, 0);
    yCurrent = random(0, yMax);

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
            if (yCurrent != 0 && xCurrent != 0) {
                --yCurrent;
                --xCurrent;
            } else {
                if (yCurrent == 0) {
                    direction = Direction::DownLeft;
                }

                if (xCurrent == 0) {
                    direction = Direction::UpRight;
                }
            }
            break;
        case Direction::UpRight:
            if (yCurrent != 0 && xCurrent != xMax) {
                --yCurrent;
                ++xCurrent;
            } else {
                if (yCurrent == 0) {
                    direction = Direction::DownRight;
                }

                if (xCurrent == xMax) {
                    direction = Direction::UpLeft;
                }
            }
            break;
        case Direction::DownLeft:
            if (yCurrent != yMax && xCurrent != 0) {
                ++yCurrent;
                --xCurrent;
            } else {
                if (yCurrent == yMax) {
                    direction = Direction::UpLeft;
                }

                if (xCurrent == 0) {
                    direction = Direction::DownRight;
                }
            }
            break;
        case Direction::DownRight:
            if (yCurrent != yMax && xCurrent != xMax) {
                ++yCurrent;
                ++xCurrent;
            } else {
                if (yCurrent == yMax) {
                    direction = Direction::UpRight;
                }

                if (xCurrent == xMax) {
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
        }
    }

    arduboy.setCursor(xCurrent, yCurrent);
    arduboy.print(title);
    arduboy.display(CLEAR_BUFFER);
}
