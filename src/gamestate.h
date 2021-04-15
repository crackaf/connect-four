#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <vector>
#include "players.h"

class GameState
{
  /**
    This is the base class for saving state of a game.
    Only a single concrete function is provided that returns the
    PlayerID of the present player

    GetPossibleMoves is a pure virtual function that must
    create and return a list of all possible moves in the
    present game state.

    GameOver() is a pure virtual function to return true if the
    game represented by the state has ended and
    return false otherwise.

    Clone() method must create a deep copy of the object
    hence requires a copy constructor;
    */

protected:
  inline static Players GamePlayers;
  unsigned int TurningPlayer; //index of player making the move
  virtual double Utility(unsigned int PlayerIndex);

public:
  unsigned int GetTurningPlayer();
  int WhoWon();
  GameState();
  bool GameOver();

  std::string GetPlayerName(int PlayerIndex = -1);
  char GetPlayerColor(int PlayerIndex = -1);

  int AddPlayer(Player *P);
  bool MakeMove();
  virtual std::vector<GameMove *> GetPossibleMoves() = 0;
  virtual bool Winning(GameMove *Move) = 0;
  virtual bool Valid(GameMove *Move) = 0;
  virtual unsigned int SelectNextPlayer();
  virtual GameState *ApplyMove(GameMove *Move) = 0;
  virtual double EvaluateState(unsigned int PlayerIndex);
  virtual GameState *Clone() = 0;
};

#endif // GAMESTATE_H
