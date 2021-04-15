#ifndef PLAYER_H
#define PLAYER_H
#include<string>
#include "gameboard.h"

class GameMove;
class GameState;
class Player
{
    public:
        Player();
        Player(const Player& P);
        Player(std::string PlayerName, char PlayerID, int DiffLevel=4);

        virtual GameMove* SuggestMove(GameState* State)=0;
        virtual double EvaluateState(GameBoard* Board);

        std::string PlayerName;
        char PlayerID; // A single 8 bit char to code the color of a player
        int DiffLevel;
};

#endif // PLAYER_H
