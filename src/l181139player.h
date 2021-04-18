#if !defined(L181139PLAYER_H)
#define L181139PLAYER_H

#include <string>

#include "Player.h"
#include "gamestate.h"
#include "connect4move.h"

class l181139player : public Player
{
public:
  l181139player(/* args */);
  l181139player(std::string name, unsigned int ID = 'P');
  ~l181139player();

  Connect4Move *SuggestMove(GameState *State);
  double EvaluateState(GameBoard *Board);
};

l181139player::l181139player(/* args */)
{
}

l181139player::l181139player(std::string name, unsigned int ID) : Player(name, ID) {}

l181139player::~l181139player()
{
}

Connect4Move *l181139player::SuggestMove(GameState *State)
{
}

double l181139player::EvaluateState(GameBoard *Board)
{
}

#endif // L181139PLAYER_H
