#include "connect4state.h"

bool Connect4State::NoMoreMoves()
{
  for (int i = 0; i < 7; i++)
    if (MoveTo[i] > -1)
      return false;
  return true;
}

/*
 0 1 2 3 4 5 6 --> cols
 1
 2
 3
 4
 5
 |
 rows
*/

int Connect4State::CheckWinner(int r, int c)
{
  /** Your Code Goes Here

    Function will check if the player that made a move at position
    (r, c) has won the game or not

    If game has been won then the players ID will be returned
    else -1 will be the return value
    */

  if (NoMoreMoves())
    return -2; // Game Drawn

  char current_player = this->GetPlayerColor();
  bool isWin = false;

  //check vertically, only need to check down
  if (!isWin)
  {
    int down = 0;
    for (int row = r + 1; row < 6 && this->State[row][c] == current_player; ++row) //moving down
      ++down;
    isWin = down >= 3 ? true : false;
  }

  //check horizontaly
  if (!isWin)
  {
    int right = 0, left = 0;
    for (int col = c - 1; col >= 0 && this->State[r][col] == current_player; --col) //moving left
      ++left;
    for (int col = c + 1; col < 7 && this->State[r][col] == current_player; ++col) //moving right
      ++right;
    isWin = (left + right) >= 3 ? true : false;
  }

  //check forward diagnal e.g //
  if (!isWin)
  {
    int upright = 0, downleft = 0;
    for (int col = c - 1, row = r + 1; col >= 0 && row <6 && this->State[row][col] == current_player; --col, ++row) //moving downleft
      ++downleft;
    for (int col = c + 1, row = r - 1; col < 7 && row >=0 && this->State[row][col] == current_player; ++col, --row) //moving upright
      ++upright;
    isWin = (downleft + upright) >= 3 ? true : false;
  }

  /*check backward diagnal e.g \\*/

  if (!isWin)
  {
    int upleft = 0, downright = 0;
    for (int col = c + 1, row = r + 1; col < 7 && row < 6 && this->State[row][col] == current_player; ++col, ++row) //moving downright
      ++downright;
    for (int col = c - 1, row = r - 1; col >= 0 && row >=0 && this->State[row][col] == current_player; --col, --row) //moving upleft
      ++upleft;
    isWin = (downright + upleft) >= 3 ? true : false;
  }

  return isWin ? this->TurningPlayer : -1;
}

double Connect4State::Utility(unsigned int PlayerIndex)
{
  // Your code goes here;
  int Winner = GamePlayers.Winner;
  if (Winner == -2)
    return 0;
  if (PlayerIndex == Winner)
    return 1;
  return -1;
  //            return 0;
}

void Connect4State::SetState(int r, int c, char ch)
{
  State[r][c] = ch;
}

Connect4State::Connect4State(Connect4State &Connect4)
{
  /**
    This copy constructor will be needed by the clone method
    */
  //no need to create copy of the static part of class

  this->TurningPlayer = Connect4.TurningPlayer;
  for (int c = 0; c < 7; c++)
  {
    this->MoveTo[c] = Connect4.MoveTo[c];
    for (int r = 0; r < 6; r++)
      this->State[r][c] = Connect4.State[r][c];
  }
  this->GamePlayers.Winner = Connect4.WhoWon();
}

char Connect4State::getState(int r, int c)
{
  return State[r][c];
}

Connect4State::Connect4State()
{
  /**
    Default constructor to initialize a new game;
    */
  this->GamePlayers.Winner = -1; // the value will be set to winning player ID or zero by the MakeMove function
  for (int c = 0; c < 7; c++)
  {
    MoveTo[c] = 5; // Largest empty row in each column
    for (int r = 0; r < 6; r++)
      State[r][c] = '.'; // Initially each cell has null char
  }
}

bool Connect4State::Winning(GameMove *Move)
{
  //// Code Here
  Connect4Move *M = static_cast<Connect4Move *>(Move);
  int column = M->GetMove();

  return CheckWinner(MoveTo[column], column) >= 0 ? true : false;
}

bool Connect4State::Valid(GameMove *Move)
{
  if (Move == nullptr)
    return false;
  Connect4Move *M = static_cast<Connect4Move *>(Move);
  int Column = M->GetMove();
  if (MoveTo[Column] < 0)
    return false;
  return true;
}

std::vector<GameMove *> Connect4State::GetPossibleMoves()
{
  /**
        This function will use the reference to MoveList to
        return all possible moves by the current player in the current state.

        return value will be true if some moves are possible and false otherwise
    */
  std::vector<GameMove *> MoveList;
  MoveList.clear();
  for (int c = 0; c < 7; c++)
  {
    if (State[0][c] == '.')
    {
      Connect4Move *T = new Connect4Move(c);
      MoveList.push_back(T);
    }
  }
  return MoveList;
}

GameState *Connect4State::ApplyMove(GameMove *Move)
{
  /**
        Apply the move on the current state and return a pointer to a
        copy of the new state.
    */
  Connect4Move *M = (static_cast<Connect4Move *>(Move));
  int c = M->GetMove(); // Column;
  State[MoveTo[c]][c] = this->GamePlayers.GetPlayerColor(TurningPlayer);
  MoveTo[c]--;
  this->GamePlayers.Winner = CheckWinner(MoveTo[c] + 1, c);
  TurningPlayer = SelectNextPlayer();
  return Clone();
}

double Connect4State::EvaluateState(unsigned int PlayerIndex)
{
  // Your code goes here

  return 0;
}

GameState *Connect4State::Clone()
{
  return new Connect4State(*this);
}
