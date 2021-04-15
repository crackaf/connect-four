#ifndef PLAYERS_H
#define PLAYERS_H
#include<string>
#include<vector>
#include"player.h"

class Players
{
    public:
        Players();
        std::string GetPlayerName(int PlayerIndex = -1);
        char GetPlayerColor(int PlayerIndex = -1);
        int AddPlayer(Player* P);
//    private:
        std::vector<Player*> PlayerList; // A non-empty list of players for the game
        unsigned int TotalPlayers; // Size of Players kept for ease of reference
        unsigned int MaxPlayers; // Maximum number of players in the Game
        unsigned int MinPlayers; // Minimum number of players in the game
        int Winner;
};

#endif // PLAYERS_H
