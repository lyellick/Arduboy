#include <Arduboy2.h>

enum class Screen { Home };
enum class Need { Hungry, Lonely, Bored, Default };
enum class Status {
    Denial,
    Anger,
    Bargaining,
    Depression,
    Acceptance,
    Annoyance,
    Sceptical
};

class Game {
   public:
    Game(Arduboy2 arduboy);

    // Tracks game time based off frame rate
    void trackTime();

    // Displays the current time span of the game
    void displayHome();

    // Toggles status, score, and timespan
    void toggleHUD() { hideHUD = !hideHUD; }

    // Checks if he has been feed in the last X hours
    void feed() { isHungry = !isHungry; }

    // Checks if he has been talked to in the last X hours
    void talkTo() { isLonely = !isLonely; }

    // Checks if he has been entertained in the last X hours
    void entertain() { isBored = !isBored; }

   private:
    Arduboy2 arduboy;

    Status status = Status::Denial;
    Need need = Need::Default;

    int16_t seconds = 0;
    int16_t minutes = 0;
    int16_t hours = 0;
    int16_t days = 0;
    int16_t years = 0;

    int16_t frames = 0;
    int16_t point = 0;

    double score = 0;
    double multiplier = .0001;

    bool hideHUD = false;
    bool isHungry = true;
    bool isLonely = true;
    bool isBored = true;

    // Ticks years, days, hours, minutes, second
    void incrementTimespan() {
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
                multiplier += .0001;

                // Hour
                if (minutes == 60) {
                    minutes = 0;
                    ++hours;
                    multiplier += .001;

                    // Day
                    if (hours == 24) {
                        hours = 0;
                        ++days;
                        multiplier += .01;

                        // Year
                        if (days == 365) {
                            days = 0;
                            ++years;
                            multiplier += .1;
                        }
                    }
                }
            }
        }
    }

    // Counts the digits in a number
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

    // Prints the current timespan
    void printTimespan() {
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
            }
        }

        if (secondsLength == 1) {
            arduboy.print(0);
        }
        arduboy.print(seconds);
    }

    // Prints the current score
    void printScore() {
        int16_t map = static_cast<int16_t>(score);
        int8_t digits = countDigits(map);
        arduboy.setCursor(WIDTH - (digits * 6), 0);
        arduboy.print(map);
    }

    // Prints Mr.Boxhead's status
    void printStatus() {
        arduboy.setCursor(0, 0);
        switch (status) {
            case Status::Denial:
            default:
                arduboy.print(F("Denial"));
                break;
        }
    }

    // Prints the missing needs such as being hungry, feeling lonely, or
    // bored.
    void printNeeds() {
        switch (need) {
            case Need::Bored:
                if (isBored) {
                    arduboy.setCursor(0, HEIGHT - 8);
                    arduboy.print("Bored");
                }
                need = Need::Hungry;
                break;
            case Need::Hungry:
                if (isHungry) {
                    arduboy.setCursor(0, HEIGHT - 8);
                    arduboy.print("Hungry");
                }
                need = Need::Lonely;
                break;
            case Need::Lonely:
                if (isLonely) {
                    arduboy.setCursor(0, HEIGHT - 8);
                    arduboy.print("Lonely");
                }
                need = Need::Default;
                break;
            case Need::Default:
            default:
                need = Need::Bored;
                break;
        }
    };
};