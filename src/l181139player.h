#if !defined(L181139PLAYER_H)
#define L181139PLAYER_H

#include <string>
#include <vector>

#include "player.h"
#include "gamestate.h"
#include "connect4move.h"
#include "connect4state.h"
#include "connect4board.h"

class l181139player : public Player
{
private:
  const int krows = 6;
  const int kcols = 7;

  struct minimax_node
  {
    int column;
    int score;
  };

  //minimax supporting functions
  bool terminalState(GameState *state);
  int getNextRow(GameState *state, int col);
  minimax_node minimax(GameState *state, int depth, int alpha, int beta, bool isMaxPlayer);

public:
  l181139player(/* args */);
  l181139player(std::string name, unsigned int ID = 'P');
  ~l181139player();

  GameMove *SuggestMove(GameState *State);

  double EvaluateState(GameBoard *Board); //this should have game state :/
  double EvaluateState(GameState *State); //wrapper function
};

int l181139player::getNextRow(GameState *State, int col)
{
  Connect4State *state = static_cast<Connect4State *>(State);
  for (int r = krows - 1; r >= 0; --r)
    if (state->getState(r, col) == '.')
      return r;
}

bool l181139player::terminalState(GameState *State)
{
  std::vector<GameMove *> valid_moves = State->GetPossibleMoves(); //valid moves in the current state

  bool terminal_state = (valid_moves.size() == 0); //no more moves
}

l181139player::minimax_node l181139player::minimax(GameState *State, int depth, int alpha, int beta, bool isMaxPlayer)
{
  Connect4State *state = static_cast<Connect4State *>(State);
  std::vector<GameMove *> valid_moves = State->GetPossibleMoves(); //valid moves in the current state

  bool terminal_state = (valid_moves.size() == 0); //no more moves

  //is ends in next move?
  //check if player can win in next move
  if (!terminal_state)
  {
    Connect4Move *bestMove = new Connect4Move(-1);
    for (int i = 0; i < kcols; ++i)
    {
      if (bestMove->SetMove(i) && state->Valid(bestMove) && state->Winning(bestMove) >= 0)
        if (state->GetPlayerColor() == this->PlayerID)
          return {-1, 100000000};
        else
          return {-1, -100000000};
    }
  }

  if (depth == 0)
  {
    return {-1, int(EvaluateState(state))};
  }

  if (isMaxPlayer)
  {
    int value = INT_MIN; //initializing score to minimum
    int bestcolumn = static_cast<Connect4Move *>(valid_moves[0])->GetMove();

    for (auto colS : valid_moves)
    {
      Connect4Move *col = static_cast<Connect4Move *>(colS);
      // int row = getNextRow(state, col->GetMove()); //available row in the current col
      GameState *state_copy = state->Clone();
      state_copy->ApplyMove(col);

      minimax_node new_node = minimax(state_copy, depth - 1, alpha, beta, false);
      int new_score = new_node.score;

      if (new_score > value)
      {
        value = new_score;
        bestcolumn = col->GetMove();
      }

      alpha = std::max(alpha, value);
      if (alpha >= beta)
        break; //purning
    }
    return {bestcolumn, value};
  }
  else //min player
  {
    int value = INT_MAX;
    int bestcolumn = static_cast<Connect4Move *>(valid_moves[0])->GetMove();

    for (auto colS : valid_moves)
    {
      Connect4Move *col = static_cast<Connect4Move *>(colS);
      GameState *state_copy = state->Clone();
      state_copy->ApplyMove(col);
      minimax_node new_node = minimax(state_copy, depth - 1, alpha, beta, false);
      int new_score = new_node.score;

      if (new_score < value)
      {
        value = new_score;
        bestcolumn = col->GetMove();
      }

      beta = std::min(beta, value);
      if (alpha >= beta)
        break; //purne
    }
    return {bestcolumn, value};
  }
}

l181139player::l181139player(/* args */)
{
}

l181139player::l181139player(std::string name, unsigned int ID) : Player(name, ID) {}

l181139player::~l181139player()
{
}

GameMove *l181139player::SuggestMove(GameState *State)
{
  minimax_node bestmove = minimax(State, this->DiffLevel, INT_MIN, INT_MAX, true);
}

double l181139player::EvaluateState(GameBoard *Board)
{
}

double l181139player::EvaluateState(GameState *State)
{
  Connect4State *state = static_cast<Connect4State *>(State);

  char mystate[6][7];
  for (int r = 0; r < krows; ++r)
    for (int c = 0; c < kcols; ++c)
      mystate[r][c] = state->getState(r, c);
  return EvaluateState(new Connect4Board(mystate));
}

#endif // L181139PLAYER_H
