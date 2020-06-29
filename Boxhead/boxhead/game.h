#include <Arduboy2.h>

enum class Screen { Home, GameOver };
enum class Need { Hungry, Lonely, Bored, Default };
enum class Status {
    Denial = 0,
    Anger = 5,
    Bargaining = 10,
    Depression = 15,
    Acceptance = 20,
    Annoyance = 25,
    Sceptical = 30
};

class Game {
   public:
    Game(Arduboy2 arduboy);

    // Tracks game time based off frame rate
    void trackTime();

    // Displays the current time span of the game
    void displayHome();

    void displayGameOver();

    // Toggles status, score, and timespan
    void toggleHUD() { hideHUD = !hideHUD; }

    // Checks if he has been feed in the last X hours
    void feed() {
        if (isHungry) {
            ++trust;
            multiplier += .00005;
            isHungry = !isHungry;
        }
    }

    // Checks if he has been talked to in the last X hours
    void talkTo() {
        if (isLonely) {
            ++trust;
            multiplier += .00005;
            isLonely = !isLonely;
        }
    }

    // Checks if he has been entertained in the last X hours
    void entertain() {
        if (isBored) {
            ++trust;
            multiplier += .00005;
            isBored = !isBored;
        }
    }

    // Checks if the multiplier is less than zero, which results in a game over
    void checkMultiplier() {
        if (multiplier <= 0) screen = Screen::GameOver;
    }

    // Gets current screen
    Screen getCurrentScreen() { return screen; };

   private:
    Arduboy2 arduboy;

    Status status = Status::Denial;
    Need need = Need::Default;
    Screen screen = Screen::Home;

    int16_t seconds = 0;
    int16_t minutes = 0;
    int16_t hours = 0;
    int16_t days = 0;
    int16_t years = 0;

    int16_t frames = 0;
    int16_t point = 0;

    double score = 0;
    double trust = 0;
    double multiplier = .0001;

    bool hideHUD = false;
    bool gameOver = false;
    bool isHungry = true;
    bool isLonely = true;
    bool isBored = true;

    // Ticks years, days, hours, minutes, second
    void incrementTimespan() {
        ++frames;

        // Second
        if (frames % 60 == 0) {
            if (frames > 90) {
                frames = 0;
            }
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

                    // Lower multiplier if not fed, talk to, or entertained in
                    // the last 24 hours
                    if (hours % 24 == 0) {
                        if (isHungry) {
                            multiplier -= 1;
                        } else {
                            isHungry = !isHungry;
                        }

                        if (isBored) {
                            multiplier -= 1;
                        } else {
                            isBored = !isBored;
                        }

                        if (isLonely) {
                            multiplier -= 1;
                        } else {
                            isLonely = !isLonely;
                        }
                    }

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

    // Counts the characters in a string
    int8_t countChars(char* string) {
        int8_t i = 0;
        while (string[i]) ++i;
        return i;
    }

    // Maps the current trust level to status
    void checkStatus() { status = static_cast<Status>(trust); };

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
        checkStatus();
        arduboy.setCursor(0, 0);
        arduboy.print(getStatus());
    };

    // Prints the missing needs such as being hungry, feeling lonely, or
    // bored.
    void printNeeds() {
        switch (need) {
            case Need::Bored:
                if (isBored && (frames > 0 && frames < 30)) {
                    arduboy.setCursor(0, HEIGHT - 8);
                    arduboy.print("Bored");
                }

                if (frames == 30) {
                    need = Need::Hungry;
                }
                break;
            case Need::Hungry:
                if (isHungry && (frames > 30 && frames < 60)) {
                    arduboy.setCursor(0, HEIGHT - 8);
                    arduboy.print("Hungry");
                }

                if (frames == 60) {
                    need = Need::Lonely;
                }
                break;
            case Need::Lonely:
                if (isLonely && (frames > 60 && frames < 90)) {
                    arduboy.setCursor(0, HEIGHT - 8);
                    arduboy.print("Lonely");
                }

                if (frames == 90) {
                    need = Need::Default;
                }
                break;
            case Need::Default:
                need = Need::Bored;
                break;
            default:
                break;
        }
    };

    // Gets status enum as string
    char* getStatus() {
        switch (status) {
            case Status::Denial:
            default:
                return "Denial";
            case Status::Anger:
                return "Anger";
            case Status::Bargaining:
                return "Bargaining";
            case Status::Depression:
                return "Depression";
            case Status::Acceptance:
                return "Acceptance";
            case Status::Annoyance:
                return "Annoyance";
            case Status::Sceptical:
                return "Sceptical";
        }
    };
};