#include <Arduboy2.h>

enum class Screen { Title, Board, Win, Loose };

class Game {
   public:
    Game(Arduboy2& arduboy, int8_t sequenceLength);

    int16_t* sequence;
    int8_t sequenceLength = 0;
    int8_t sequenceIndex = 0;

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

    void validateInputInSequence(int16_t button) {
        if (sequenceIndex < sequenceLength) {
            int16_t expectedButton = sequence[sequenceIndex];
            arduboy.setCursor(WIDTH - 32, 0);
            arduboy.print(expectedButton);
            for (size_t i = 0; i < sequenceIndex; ++i) {
                arduboy.setCursor(0, i * 8);
                arduboy.print(sequence[i]);
            }

            if (arduboy.justPressed(button)) {
                if (button != 0) {
                    if (button == expectedButton) {
                        ++sequenceIndex;
                    } else {
                        screen = Screen::Loose;
                    }
                }
            }
        } else {
            screen = Screen::Win;
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
        sequenceIndex = 0;
        sequence = new int16_t[sequenceLength];
        generateSequence();
        screen = Screen::Title;
    };
};