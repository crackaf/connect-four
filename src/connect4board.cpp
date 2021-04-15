#include "connect4board.h"

Connect4Board::Connect4Board(char State[6][7])
{
  for (int c = 0; c < 7; c++)
  {
    for (int r = 0; r < 6; r++)
      this->State[r][c] = State[r][c];
  }
}
