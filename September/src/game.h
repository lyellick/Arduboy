#include <Arduboy2.h>

enum class Screen { Title, Board, Win, Loose };

class Game {
   public:
    Game(Arduboy2& arduboy, int8_t sequenceLength);

    int16_t* sequence;
    int8_t sequenceLength = 0;
    int8_t sequenceIndex = 0;
    int8_t sequenceEndBound = 0;
    int8_t sequenceSpeed = 60;

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

    bool presentedSequence = false;

    // Checks the current input in next index of sequence
    void validateInputInSequence(int16_t button) {
        int16_t expectedButton = sequence[sequenceIndex];
        if (button == expectedButton) {
            ++sequenceIndex;
        } else {
            screen = Screen::Loose;
        }
    };

    // Shows the sequence to remember
    void showSequence() {
        if (arduboy.frameCount % sequenceSpeed != 0) {
            switch (sequence[sequenceEndBound]) {
                case UP_BUTTON:
                    printCenter("UP");
                    break;
                case RIGHT_BUTTON:
                    printCenter("RIGHT");
                    break;
                case DOWN_BUTTON:
                    printCenter("DOWN");
                    break;
                case LEFT_BUTTON:
                    printCenter("LEFT");
                    break;
                case A_BUTTON:
                    printCenter("A");
                    break;
                case B_BUTTON:
                    printCenter("B");
                    break;
                default:
                    break;
            }
        } else {
            if (sequenceEndBound < sequenceLength - 1) {
                ++sequenceEndBound;
            } else {
                presentedSequence = true;
            }
        }
    };

    // Generates a new sequence
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

    // Resets all game variables to orginial state
    void resetGame() {
        presentedSequence = false;
        sequenceEndBound = 0;
        sequenceIndex = 0;
        delete[] sequence;
        sequence = new int16_t[sequenceLength];
        generateSequence();
        screen = Screen::Title;
    };

    // Counts the characters in a string
    int8_t countChars(char* string) {
        int8_t i = 0;
        while (string[i]) ++i;
        return i;
    }

    // Gets length of text and centers on screen
    void printCenter(char* text) {
        arduboy.setCursor((WIDTH - (countChars(text) * 6)) / 2, HEIGHT / 2);
        arduboy.print(text);
    }
};