/*
  Moves "Boxhead" around screen like a DVD screen saver.
*/

#include <Arduboy2.h>

Arduboy2 arduboy;

int x_min, x_max, x_center, y_min, y_max, y_center;

const int CHAR_WIDTH = 6;
const int CHAR_HEIGHT = 8;

String title = String("Boxhead");

void setup()
{
  int len = title.length() * CHAR_WIDTH;

  x_min = 0;
  y_min = 0;

  x_max = WIDTH - len;
  y_max = HEIGHT - CHAR_HEIGHT;

  x_center = (WIDTH - len)/2;
  y_center = (HEIGHT - (CHAR_HEIGHT))/2;

  arduboy.begin();
  arduboy.clear();
}

void loop()
{
  arduboy.clear();
  arduboy.setCursor(x_center, y_center);
  arduboy.print(title);
  arduboy.display();
}