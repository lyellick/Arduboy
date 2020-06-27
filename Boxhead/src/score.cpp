#include <Arduboy2.h>
#include <score.h>

Score::Score()
    : point(0),
      score(0),
      multiplier(.001),
      frames(0),
      seconds(0),
      minutes(0),
      hours(0),
      days(0),
      years(0){

      };

void Score::trackGameTime() {
    ++frames;
    if (frames == 60) {
        frames = 0;
        ++seconds;
        setScore();
        if (seconds == 60) {
            seconds = 0;
            ++minutes;
            multiplier += .001;
            if (minutes == 60) {
                minutes = 0;
                ++hours;
                multiplier += .01;
                if (hours == 24) {
                    hours = 0;
                    ++days;
                    multiplier += .1;
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

double Score::getScore() { return score; };
double Score::getMultiplier() { return multiplier; }