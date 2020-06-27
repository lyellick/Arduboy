#include <Arduboy2.h>

class Score {
   private:
    int16_t point;
    double score;
    double multiplier;

    void setScore() {
        ++point;
        score = point * multiplier;
    };

   public:
    int8_t frames;

    int8_t seconds;
    int8_t minutes;
    int8_t hours;
    int16_t days;
    int32_t years;

    Score();

    // Tracks game time
    void trackGameTime();
    double getScore();
    double getMultiplier();
};