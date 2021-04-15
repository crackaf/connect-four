#ifndef AUTOC4PLAYER_H
#define AUTOC4PLAYER_H
#include "Player.h"
#include "gamestate.h"
#include "connect4move.h"

class AutoC4Player : public Player
{
public:
  AutoC4Player(char Color = 'A');
  Connect4Move *SuggestMove(GameState *State);
  double EvaluateState(GameBoard *Board);
};

#endif // AUTOC4PLAYER_H
