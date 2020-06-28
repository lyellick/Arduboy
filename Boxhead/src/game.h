#include <Arduboy2.h>

enum class Screen { Home };

class Game {
   public:
    Game(Arduboy2 arduboy);

    // Tracks game time based off frame rate
    void trackTime();

    // Returns score
    double getScore();

    // Returns multiplier
    double getMultiplier();

    // Displays the current time span of the game
    void displayHome();

    template <typename T>
    T countDigits(T number) {
        int8_t digits = 0;
        if (number == 0) ++digits;
        while (number) {
            number /= 10;
            ++digits;
        }
        return digits;
    }

    template <typename T>
    int16_t printNextTimespan(int8_t count, T span, bool includeColon) {
        if (includeColon) {
            count += (countDigits(span) + 1);
        } else {
            count += countDigits(span);
        }

        arduboy.setCursor(WIDTH - (count * 6), HEIGHT - 8);
        arduboy.print(span);

        if (includeColon) arduboy.print(F(":"));

        return count;
    }

   private:
    Arduboy2 arduboy;

    int16_t seconds = 0;
    int16_t minutes = 0;
    int16_t hours = 0;
    int16_t days = 0;
    int16_t years = 0;

    int16_t frames = 0;
    int16_t point = 0;

    double score = 0;
    double multiplier = .001;
};