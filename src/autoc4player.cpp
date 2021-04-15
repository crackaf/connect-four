#include "autoc4player.h"

AutoC4Player::AutoC4Player(char Color) : Player("Auto:Random", Color)
{
  // Just call the base constructor
}

double AutoC4Player::EvaluateState(GameBoard *Board)
{
  // Board Evaluation Area;
  // This auto-player is not using it.
    return 0;
}

Connect4Move *AutoC4Player::SuggestMove(GameState *State)
{
  Connect4Move *Move = new Connect4Move;

  std::vector<GameMove *> Moves = State->GetPossibleMoves();
  int Total = int(Moves.size());

  if (Total == 0)
  {
    return nullptr;
  }

  int MoveIndex = int(float(rand()) / RAND_MAX * Total);
  Move->SetMove(static_cast<Connect4Move *>(Moves[MoveIndex])->GetMove());

  for (int i = 0; i < Total; i++)
    delete Moves[i];

  Moves.clear();
  return Move;
}
