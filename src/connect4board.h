#ifndef CONNECT4BOARD_H
#define CONNECT4BOARD_H

#include "gameboard.h"

class Connect4Board : public GameBoard
{
public:
  Connect4Board(char State[6][7]);
  char State[6][7];
};

#endif // CONNECT4BOARD_H
