#include "connect4move.h"

Connect4Move::Connect4Move(int Column) : GameMove("Connect 4 Move")
{
  SetMove(Column);
}

int Connect4Move::GetMove()
{
  return Column;
}

bool Connect4Move::SetMove(int Column)
{
  if (Column < 0 || Column > 6)
  {
    this->Column = 0;
    return false;
  }
  this->Column = Column;
  return true;
}
