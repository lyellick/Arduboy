#include <Arduboy2.h>

enum class Screen { Title, Board, Win, Loose };

class Game {
   public:
    Game(Arduboy2& arduboy, int8_t sequenceLength);

    int16_t* sequence;
    int8_t sequenceLength = 0;
    int8_t sequenceIndex = 0;
    int8_t sequenceEndBound = 0;
    int8_t sequenceSpeed = 100;

    // Gets current screen
    Screen getCurrentScreen() { return screen; };

    // Display title screen
    void displayTitle(bool anyKeyPressed);

    // Display win screen
    void displayWinScreen(bool anyKeyPressed);

    // Display loose screen
    void displayLooseScreen(bool anyKeyPressed);

    // Display board screen
    void displayBoard(int16_t button);

    // Sets up game
    void initialize();

   private:
    Arduboy2& arduboy;

    Screen screen = Screen::Title;

    bool presentedNextSequence = false;

    void validateInputInSequence(int16_t button) {
        int16_t expectedButton = sequence[sequenceIndex];
        if (button == expectedButton) {
            ++sequenceIndex;
            presentedNextSequence = false;
        } else {
            screen = Screen::Loose;
        }
    };

    void showCurrentSequence() {
        if (arduboy.frameCount % sequenceSpeed != 0) {
            arduboy.setCursor(0, 0);
            arduboy.print(sequence[sequenceEndBound]);
        } else {
            if (sequenceEndBound != sequenceIndex) {
                ++sequenceEndBound;
            } else {
                presentedNextSequence = true;
                sequenceEndBound = 0;
            }
        }
    };

    void generateSequence() {
        for (size_t i = 0; i < sequenceLength; ++i) {
            int8_t rand = random(6);
            switch (rand) {
                case 0:
                    sequence[i] = UP_BUTTON;  // 128
                    break;
                case 1:
                    sequence[i] = RIGHT_BUTTON;  // 64
                    break;
                case 2:
                    sequence[i] = DOWN_BUTTON;  // 16
                    break;
                case 3:
                    sequence[i] = LEFT_BUTTON;  // 32
                    break;
                case 4:
                    sequence[i] = A_BUTTON;  // 4
                    break;
                case 5:
                    sequence[i] = B_BUTTON;  // 8
                    break;
                default:
                    break;
            }
        }
    };

    void resetGame() {
        presentedNextSequence = false;
        sequenceIndex = 0;
        sequence = new int16_t[sequenceLength];
        generateSequence();
        screen = Screen::Title;
    };
};