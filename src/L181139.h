#error this is incomplete file don't include

#ifndef L181139_H_
#define L181139_H_

#include <string>
#include <vector>
#include <algorithm>

#include "player.h"
#include "connect4board.h"
#include "connect4state.h"
#include "connect4move.h"

class L181139
    : public Player
{
public:
  L181139();
  L181139(std::string name, unsigned int id = 'P', int DifficultyLevel = 4);
  ~L181139();

  virtual GameMove *SuggestMove(GameState *);
  virtual double EvaluateState(GameBoard *);

  //functions that should have been in connect4state if the structure was good
  GameBoard *StateToBoard(GameState *);
  bool isWinState(GameState *, int player);

private:
  const unsigned int kRows = 6;
  const unsigned int kCols = 7;
  const unsigned int kScore = 4;

  //minimax supporting functions
  int _GetNextRow(GameState *, int col);
  auto minimax(GameState *, int depth, int alpha, int beta, bool isMaxPlayer);

  //supporting evaluate state functions
  double _EvaluatePiece(std::string piece);
};

L181139::L181139(/* args */) : Player("L181139", 'P') {}

L181139::L181139(std::string name, unsigned int id, int DifficultyLevel) : Player(name, id, DifficultyLevel) {}

L181139::~L181139() {}

GameMove *L181139::SuggestMove(GameState *State)
{
  return new Connect4Move(minimax(State, this->DiffLevel, INT_MIN, INT_MAX, true).column);
}

// scoring every position with respective to my ID
double L181139::EvaluateState(GameBoard *Board)
{

  Connect4Board *c4board = static_cast<Connect4Board *>(Board);

  char board[6][7];
  double score = 0;

  for (int r = 0; r < kRows; ++r)
    for (int c = 0; c < kCols; ++c)
      board[r][c] = c4board->State[r][c];

  //center column score --> important if game is equal
  int centerpoints = 0;
  for (int r = 0; r < kRows; ++r)
    if (board[r][kCols / 2] == this->PlayerID) //center
      ++centerpoints;
  score += double(centerpoints) * 30;

  //verticle scores
  for (int c = 0; c < kCols; ++c)
  {
    std::string col;
    for (int r = 0; r < kRows; ++r)
      col.push_back(board[r][c]);
    for (int r = 0; r < kRows - kScore + 1; ++r)
    {
      std::string subcol = col.substr(r, kScore); //get 4 coins/stones
      score += _EvaluatePiece(subcol);            //evaluate every 4 coins/stones seperately
    }
  }

  //horizontal scores
  for (int r = 0; r < kRows; ++r)
  {
    std::string row;
    for (int c = 0; c < kCols; ++c)
      row.push_back(board[r][c]);
    for (int c = 0; c < kCols - kScore + 1; ++c)
    {
      std::string subrow = row.substr(c, kScore);
      score += _EvaluatePiece(subrow);
    }
  }

  //forward diagnol e.g //
  for (int r = 0; r < kRows - kScore + 1; ++r)
  {
    for (int c = 0; c < kCols - kScore + 1; ++c)
    {
      std::string diagnol;
      for (int i = 0; i < kScore; ++i)
        diagnol.push_back(board[r + i][c + i]);
      score += _EvaluatePiece(diagnol);
    }
  }

  //backward diagnol , negative slope
  for (int r = 0; r < kRows - kScore + 1; ++r)
  {
    for (int c = 0; c < kCols - kScore + 1; ++c)
    {
      std::string diagnol;
      for (int i = 0; i < kScore; ++i)
        diagnol.push_back(board[r + kScore - 1 - i][c + i]);
      score += _EvaluatePiece(diagnol);
    }
  }

  return score;
}

GameBoard *L181139::StateToBoard(GameState *State)
{
  Connect4State *state = static_cast<Connect4State *>(State);

  char mystate[6][7];
  for (int r = 0; r < kRows; ++r)
    for (int c = 0; c < kCols; ++c)
      mystate[r][c] = state->getState(r, c);

  return new Connect4Board(mystate);
}

bool L181139::isWinState(GameState *State, int player)
{
  Connect4State *state = static_cast<Connect4State *>(State);
  char current_player = state->GetPlayerColor(player);

  //check vertically
  for (int c = 0; c < kCols; ++c)
    for (int r = 0; r < kRows - kScore + 1; ++r)
      if (state->getState(r, c) == current_player && state->getState(r + 1, c) == current_player && state->getState(r + 2, c) == current_player && state->getState(r + 3, c) == current_player)
        return true;

  //check horizontaly
  for (int c = 0; c < kCols - kScore + 1; ++c)
    for (int r = 0; r < kRows; ++r)
      if (state->getState(r, c) == current_player && state->getState(r, c + 1) == current_player && state->getState(r, c + 2) == current_player && state->getState(r, c + 3) == current_player)
        return true;

  //check forward diagnal e.g //
  for (int c = 0; c < kCols - kScore + 1; ++c)
    for (int r = 0; r < kRows - kScore + 1; ++r)
      if (state->getState(r, c) == current_player && state->getState(r + 1, c + 1) == current_player && state->getState(r + 2, c + 2) == current_player && state->getState(r + 3, c + 3) == current_player)
        return true;

  /*check backward diagnal e.g \\*/
  for (int c = 0; c < kCols - kScore + 1; ++c)
    for (int r = kScore - 1; r < kRows; ++r)
      if (state->getState(r, c) == current_player && state->getState(r - 1, c + 1) == current_player && state->getState(r - 2, c + 2) == current_player && state->getState(r - 3, c + 3) == current_player)
        return true;

  return false;
}

int L181139::_GetNextRow(GameState *State, int col)
{
  Connect4State *state = static_cast<Connect4State *>(State);
  for (int r = kRows - 1; r >= 0; --r)
    if (state->getState(r, col) == '.')
      return r;
  return -1;
}

auto L181139::minimax(GameState *State, int depth, int alpha, int beta, bool isMaxPlayer)
{
  Connect4State *state = static_cast<Connect4State *>(State);
  std::vector<GameMove *> valid_moves = State->GetPossibleMoves(); //valid moves in the current state

  if (valid_moves.size() == 0) //no more moves
    return std::vector{NULL, 0};
  else
  { //is ends in next move?
    //check if player can win in next move
    GameState *state_test = state->Clone();
    if (isWinState(state_test, state->GetTurningPlayer())) //my own player checking
      return std::vector{NULL, 100000000};
    if (isWinState(state_test, state->SelectNextPlayer())) //opposition checking
      return std::vector{NULL, -100000000};
  }
  if (depth == 0)
    return {-1, EvaluateState(StateToBoard(State))}; //returns the evaluation score

  int value = isMaxPlayer ? INT_MIN : INT_MAX; //initializing score to minimum:maximum
  int bestcolumn = static_cast<Connect4Move *>(valid_moves[0])->GetMove();

  for (auto move : valid_moves)
  {
    GameState *state_copy = state->Clone();
    state_copy->ApplyMove(move);

    if (isMaxPlayer)
    {
      int new_score = minimax(state_copy, depth - 1, alpha, beta, false).score;

      if (new_score > value) //selecting best score for our AI
      {
        value = new_score;
        bestcolumn = static_cast<Connect4Move *>(move)->GetMove();
      }

      alpha = std::max(alpha, value);
    }
    else
    {
      int new_score = minimax(state_copy, depth - 1, alpha, beta, true).score;

      if (new_score < value) //selecting worst score for us
      {
        value = new_score;
        bestcolumn = static_cast<Connect4Move *>(move)->GetMove();
      }

      beta = std::min(beta, value);
    }

    if (alpha >= beta)
      break; //purning
  }

  return std::vector{bestcolumn, value};
}

double L181139::_EvaluatePiece(std::string line)
{
  double score = 0;

  int my_count = std::count(line.begin(), line.end(), this->PlayerID); //count my stones
  int null_count = std::count(line.begin(), line.end(), '.');          //count empty slots
  int opposition_count = std::count_if(line.begin(), line.end(), [&](char c) {
    return (c != this->PlayerID && c != '.');
  }); //count opponent stones

  if (my_count >= 4)
    score += 100;
  else if (my_count == 3 && null_count == 1)
    score += 5;
  else if (my_count == 2 && null_count == 2)
    score += 2;
  else if (opposition_count == 2 && null_count == 2)
    score -= 1;
  else if (opposition_count == 3 && null_count == 1)
    score -= 4;

  return score;
}

#endif // L181139_H_