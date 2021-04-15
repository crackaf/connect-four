#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

class HumanPlayer : public Player
{
public:
  virtual GameMove *SuggestMove(GameState *State);
  HumanPlayer(std::string Name, unsigned int ID);
};

#endif // HUMAN_PLAYER_H
