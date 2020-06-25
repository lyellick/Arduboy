/*
  Moves "Hello, World!" around screen like a DVD screen saver.
*/

#include <Arduboy2.h>

Arduboy2 arduboy;

enum Direction { UpLeft, UpRight, DownLeft, DownRight, Default };

int x_min, x_max, x_center, x_current, y_min, y_max, y_center, y_current, speed;

bool paused;

Direction direction;

const int CHAR_WIDTH = 6;
const int CHAR_HEIGHT = 8;

String title = String("Hello, World!");

void setup() {
    randomSeed(analogRead(0));

    // title length in pixels
    int len = title.length() * CHAR_WIDTH;

    // axis minimums
    x_min = 0, y_min = 0;

    // axis maximums
    x_max = WIDTH - len, y_max = HEIGHT - CHAR_HEIGHT;

    // axis center
    x_center = (WIDTH - len) / 2, y_center = (HEIGHT - (CHAR_HEIGHT)) / 2;

    // current cursor initialization
    x_current = random(0, x_min), y_current = random(0, y_max);

    // set inital direction
    direction = (Direction)random(0, Default);

    // set speed
    speed = 10;

    // set paused state
    paused = false;

    arduboy.begin();
    arduboy.clear();
}

void moveTitle(int speed) {
    arduboy.clear();
    arduboy.setCursor(x_current, y_current);
    arduboy.print(title);
    arduboy.display();
    delay(speed);
}

void nextPosition() {
    switch (direction) {
        case UpLeft:
            if (y_current != y_min && x_current != x_min) {
                y_current--;
                x_current--;
            } else {
                if (y_current == y_min) {
                    direction = DownLeft;
                }

                if (x_current == x_min) {
                    direction = UpRight;
                }
            }
            break;
        case UpRight:
            if (y_current != y_min && x_current != x_max) {
                y_current--;
                x_current++;
            } else {
                if (y_current == y_min) {
                    direction = DownRight;
                }

                if (x_current == x_max) {
                    direction = UpLeft;
                }
            }
            break;
        case DownLeft:
            if (y_current != y_max && x_current != x_min) {
                y_current++;
                x_current--;
            } else {
                if (y_current == y_max) {
                    direction = UpLeft;
                }

                if (x_current == x_min) {
                    direction = DownRight;
                }
            }
            break;
        case DownRight:
            if (y_current != y_max && x_current != x_max) {
                y_current++;
                x_current++;
            } else {
                if (y_current == y_max) {
                    direction = UpRight;
                }

                if (x_current == x_max) {
                    direction = DownLeft;
                }
            }
            break;
        default:
            break;
    }
}

void loop() {
    arduboy.pollButtons();
    if (arduboy.justPressed(UP_BUTTON)) {
        if (speed != 0) {
            speed--;
        }
    }
    if (arduboy.justPressed(DOWN_BUTTON)) {
        speed += 5;
    }
    if (arduboy.justPressed(A_BUTTON)) {
        speed = 10;
    }
    if (arduboy.justPressed(B_BUTTON)) {
        paused = !paused;
    }
    if (!paused) {
        nextPosition();
        moveTitle(speed);
    }
}
