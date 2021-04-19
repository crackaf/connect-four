#include <iostream>
#include <vector>
#include <iomanip>

#include "Connect4State.h"
#include "humanplayer.h"
#include "autoc4player.h"
#include "l181139AIplayer.h"

using namespace std;

void BlankLines(int n)
{
  for (int i = 0; i < n; i++)
    cout << "\n";
}

void ShowConnect4(GameState *C)
{
  Connect4State *C4 = static_cast<Connect4State *>(C);
  string P1 = C4->GetPlayerName(0);
  string P2 = C4->GetPlayerName(1);

  cout << "\t\t" << P1 << "\t\t vs \t\t" << P2;
  BlankLines(3);
  for (int i = 1; i < 8; i++)
  {
    if (i == 1)
      cout << setw(8) << i;
    else
      cout << setw(11) << i;
  }
  BlankLines(3);

  for (int r = 0; r < 6; r++)
  {
    for (int c = 0; c < 7; c++)
    {
      if (c == 0)
        cout << setw(2) << "|";
      char PlayerCode = C4->getState(r, c);
      cout << setw(6) << PlayerCode << setw(5) << "|";
    }
    cout << endl;

    for (int b = 0; r < 5 && b < 2; b++)
    {
      for (int c = 0; r < 5 && c < 7; c++)
      {
        if (c == 0)
          cout << setw(2) << "|";
        cout << setw(6) << ' ' << setw(5) << "|";
      }
      cout << endl;
    }
  }
  for (int i = 0; i < 80; i++)
    cout << char(220);

  if (C4->GetTurningPlayer() == 1)
    cout << endl
         << "Turn of " << P2;
  else
    cout << endl
         << "Turn of " << P1;
  cout << endl
       << endl;
}

int main()
{
  Player *Players[3];
  int InvalidMoveCount[3];
  Players[0] = new HumanPlayer("Human1", 'H');
  Players[1] = new l181139AIplayer("Malik", 'P');
  //Players[1] = new HumanPlayer("Human2", 'K');
  //Players[1] = new AutoC4Player('L');
  Players[2] = new AutoC4Player('B');
  int TotalPlayers = 2;

  for (int i = 0; i < TotalPlayers - 1; i++)
  {
    for (int j = i + 1; j < TotalPlayers; j++)
    {
      GameState *C4 = new Connect4State();
      C4->AddPlayer(Players[i]);
      C4->AddPlayer(Players[j]);

      int TurningPlayer;

      int Toggle = 1;
      while (!C4->GameOver())
      {
        if (Toggle)
        {
          ShowConnect4(C4);
        }
        Toggle = (Toggle + 1) % 2;

        TurningPlayer = C4->GetTurningPlayer();
        cout << "Player Turning: " << C4->GetPlayerName() << "-" << C4->GetPlayerColor() << endl;

        if (!C4->MakeMove())
        {
          TurningPlayer = C4->GetTurningPlayer();
          InvalidMoveCount[TurningPlayer]++;
          cout << "made invalid Move\n";
          ShowConnect4(C4);
          system("pause");
        }
      }
      ShowConnect4(C4);
    }
  }

  return 0;
}
