#ifndef GAMEMOVE_H
#define GAMEMOVE_H
#include <string>

class GameMove
{
  /*
   Class to represent a single game move
  */
public:
  GameMove(std::string Description = "Default Move Description");
  std::string toString();

private:
  std::string Description;
};
#endif // GAMEMOVE_H
