#include "player.h"
#include <iostream>
#include "humanplayer.h"
#include "connect4move.h"

using namespace std;

GameMove *HumanPlayer::SuggestMove(GameState *State)
{
  int Column;
  cout << "Please enter your move (1-7)";
  cin >> Column;
  Connect4Move *Move = new Connect4Move();
  Move->SetMove(Column - 1); // Column;
  // cout<<Column<<" Move set to "<<Move->GetMove();
  return Move;
}

HumanPlayer::HumanPlayer(string Name, unsigned int ID) : Player(Name, ID)
{
}
