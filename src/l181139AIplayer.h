#if !defined(L181139AIPLAYER_H)
#define L181139AIPLAYER_H

#include <string>
#include <vector>
#include <algorithm>

#include "player.h"
#include "gamestate.h"
#include "connect4move.h"
#include "connect4state.h"
#include "connect4board.h"

class l181139AIplayer : public Player
{
private:
  const int krows = 6;
  const int kcols = 7;
  const int kscore = 4;

  struct minimax_node
  {
    int column;
    int score;
  };

  //minimax supporting functions
  int getNextRow(GameState *state, int col);
  minimax_node minimax(GameState *state, int depth, int alpha, int beta, bool isMaxPlayer);

  //supporting evaluate state functions
  double EvaluateSubState(std::string substate);

public:
  l181139AIplayer(/* args */);
  l181139AIplayer(std::string name, unsigned int ID = 'P', int DifficultyLevel = 4);
  ~l181139AIplayer();

  GameMove *SuggestMove(GameState *State);

  double EvaluateState(GameBoard *Board); //this should have game state :/
  double EvaluateState(GameState *State); //wrapper function

  //functions that should have been in connect4 state if the structure was good

  //because GameState->Winning() only check win for currect player and there is no way to changing the currect player without ApplyMove()
  bool isWinState(GameState *State, int player);
};

int l181139AIplayer::getNextRow(GameState *State, int col)
{
  Connect4State *state = static_cast<Connect4State *>(State);
  for (int r = krows - 1; r >= 0; --r)
    if (state->getState(r, col) == '.')
      return r;
  return -1;
}

l181139AIplayer::minimax_node l181139AIplayer::minimax(GameState *State, int depth, int alpha, int beta, bool isMaxPlayer)
{
  Connect4State *state = static_cast<Connect4State *>(State);
  std::vector<GameMove *> valid_moves = State->GetPossibleMoves(); //valid moves in the current state

  bool terminal_state = (valid_moves.size() == 0); //no more moves

  if (terminal_state)
    return {NULL, 0};

  //is ends in next move?
  //check if player can win in next move
  if (!terminal_state)
  {
    GameState *state_test = state->Clone();
    if (isWinState(state_test, state->GetTurningPlayer())) //my own player checking
      return {NULL, 100000000};
    if (isWinState(state_test, state->SelectNextPlayer())) //opposition checking
      return {NULL, -100000000};
  }

  if (depth == 0)
  {
    return {-1, int(EvaluateState(state))}; //returns the evaluation score
  }

  if (isMaxPlayer)
  {
    int value = INT_MIN; //initializing score to minimum
    int bestcolumn = static_cast<Connect4Move *>(valid_moves[0])->GetMove();

    for (auto colS : valid_moves)
    {
      Connect4Move *col = static_cast<Connect4Move *>(colS);
      GameState *state_copy = state->Clone();

      state_copy->ApplyMove(col); //AI move
      int new_score = minimax(state_copy, depth - 1, alpha, beta, false).score;

      if (new_score > value) //selecting best score for our AI
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

      state_copy->ApplyMove(col); //opposition move
      int new_score = minimax(state_copy, depth - 1, alpha, beta, true).score;

      if (new_score < value) //selecting worst score for us
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

l181139AIplayer::l181139AIplayer(/* args */) : Player("L181139", 'P') {}

l181139AIplayer::l181139AIplayer(std::string name, unsigned int ID, int DifficultyLevel) : Player(name, ID, DifficultyLevel) {}

l181139AIplayer::~l181139AIplayer() {}

GameMove *l181139AIplayer::SuggestMove(GameState *State)
{
  return new Connect4Move(minimax(State, this->DiffLevel, INT_MIN, INT_MAX, true).column);
}

double l181139AIplayer::EvaluateSubState(std::string line)
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

// scoring every position with respective to my ID
double l181139AIplayer::EvaluateState(GameBoard *Board)
{
  char board[6][7];
  double score = 0;

  for (int r = 0; r < krows; ++r)
    for (int c = 0; c < kcols; ++c)
      board[r][c] = static_cast<Connect4Board *>(Board)->State[r][c];

  //center column score --> important if game is equal
  int centerpoints = 0;
  for (int r = 0; r < krows; ++r)
    if (board[r][kcols / 2] == this->PlayerID) //center
      ++centerpoints;
  score += double(centerpoints) * 30;

  //verticle scores
  for (int c = 0; c < kcols; ++c)
  {
    std::string col;
    for (int r = 0; r < krows; ++r)
      col.push_back(board[r][c]);
    for (int r = 0; r < krows - kscore + 1; ++r)
    {
      std::string subcol = col.substr(r, kscore); //get 4 coins/stones
      score += EvaluateSubState(subcol);          //evaluate every 4 coins/stones seperately
    }
  }

  //horizontal scores
  for (int r = 0; r < krows; ++r)
  {
    std::string row;
    for (int c = 0; c < kcols; ++c)
      row.push_back(board[r][c]);
    for (int c = 0; c < kcols - kscore + 1; ++c)
    {
      std::string subrow = row.substr(c, kscore);
      score += EvaluateSubState(subrow);
    }
  }

  //forward diagnol e.g //
  for (int r = 0; r < krows - kscore + 1; ++r)
  {
    for (int c = 0; c < kcols - kscore + 1; ++c)
    {
      std::string diagnol;
      for (int i = 0; i < kscore; ++i)
        diagnol.push_back(board[r + i][c + i]);
      score += EvaluateSubState(diagnol);
    }
  }

  //backward diagnol , negative slope
  for (int r = 0; r < krows - kscore + 1; ++r)
  {
    for (int c = 0; c < kcols - kscore + 1; ++c)
    {
      std::string diagnol;
      for (int i = 0; i < kscore; ++i)
        diagnol.push_back(board[r + kscore - 1 - i][c + i]);
      score += EvaluateSubState(diagnol);
    }
  }

  return score;
}

double l181139AIplayer::EvaluateState(GameState *State)
{
  Connect4State *state = static_cast<Connect4State *>(State);

  char mystate[6][7];
  for (int r = 0; r < krows; ++r)
    for (int c = 0; c < kcols; ++c)
      mystate[r][c] = state->getState(r, c);

  return EvaluateState(new Connect4Board(mystate));
}

bool l181139AIplayer::isWinState(GameState *State, int player)
{
  Connect4State *state = static_cast<Connect4State *>(State);
  char current_player = state->GetPlayerColor(player);

  //check vertically
  for (int c = 0; c < kcols; ++c)
    for (int r = 0; r < krows - kscore + 1; ++r)
      if (state->getState(r, c) == current_player && state->getState(r + 1, c) == current_player && state->getState(r + 2, c) == current_player && state->getState(r + 3, c) == current_player)
        return true;

  //check horizontaly
  for (int c = 0; c < kcols - kscore + 1; ++c)
    for (int r = 0; r < krows; ++r)
      if (state->getState(r, c) == current_player && state->getState(r, c + 1) == current_player && state->getState(r, c + 2) == current_player && state->getState(r, c + 3) == current_player)
        return true;

  //check forward diagnal e.g //
  for (int c = 0; c < kcols - kscore + 1; ++c)
    for (int r = 0; r < krows - kscore + 1; ++r)
      if (state->getState(r, c) == current_player && state->getState(r + 1, c + 1) == current_player && state->getState(r + 2, c + 2) == current_player && state->getState(r + 3, c + 3) == current_player)
        return true;

  /*check backward diagnal e.g \\*/
  for (int c = 0; c < kcols - kscore + 1; ++c)
    for (int r = kscore - 1; r < krows; ++r)
      if (state->getState(r, c) == current_player && state->getState(r - 1, c + 1) == current_player && state->getState(r - 2, c + 2) == current_player && state->getState(r - 3, c + 3) == current_player)
        return true;

  return false;
}

#endif // L181139PLAYER_H
