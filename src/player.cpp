#include "player.h"

Player::Player()
{
  this->PlayerName = "Name";
  this->PlayerID = -1;
  this->DiffLevel = 0;
}

Player::Player(const Player &P)
{
  this->PlayerName = P.PlayerName;
  this->PlayerID = P.PlayerID;
  this->DiffLevel = P.DiffLevel;
}

Player::Player(std::string PlayerName, char PlayerID, int DiffLevel)
{
  this->PlayerName = PlayerName;
  this->PlayerID = PlayerID;
  this->DiffLevel = DiffLevel;
}

double Player::EvaluateState(GameBoard *Board)
{
  return 0;
}
