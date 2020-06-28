#include "game.h"

#include <Arduboy2.h>

Game::Game(Arduboy2 arduboy) : arduboy(arduboy){};

double Game::getScore() { return score; };
double Game::getMultiplier() { return multiplier; };

void Game::trackTime() {
    ++frames;

    // Second
    if (frames == 60) {
        frames = 0;
        ++seconds;
        ++point;
        score = point * multiplier;

        // Minute
        if (seconds == 60) {
            seconds = 0;
            ++minutes;
            multiplier += .001;

            // Hour
            if (minutes == 60) {
                minutes = 0;
                ++hours;
                multiplier += .01;

                // Day
                if (hours == 24) {
                    hours = 0;
                    ++days;
                    multiplier += .1;

                    // Year
                    if (days == 365) {
                        days = 0;
                        ++years;
                        multiplier += 1;
                    }
                }
            }
        }
    }
};

void Game::displayHome() {
    int8_t count = 0;

    int16_t secondsLength = countDigits(seconds);

    int16_t timespan[] = {years, days, hours, minutes};

    for (size_t i = 0; i < 4; ++i) {
        int16_t span = timespan[i];
        int8_t digits = countDigits(span);
        if (span > 0) {
            count += digits + 1;
            if (digits == 1) {
                ++count;
            }
        }
    }

    count += secondsLength;
    if (secondsLength == 1) {
        ++count;
    }

    arduboy.setCursor(WIDTH - (count * 6), HEIGHT - 8);

    for (size_t i = 0; i < 4; i++) {
        int16_t span = timespan[i];
        int8_t digits = countDigits(span);
        if (span > 0) {
            if (digits == 1) {
                arduboy.print(0);
            }
            arduboy.print(span);
            arduboy.print(F(":"));
        };
    }

    if (secondsLength == 1) {
        arduboy.print(0);
    }
    arduboy.print(seconds);
};
