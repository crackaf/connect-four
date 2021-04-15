#include "players.h"

Players::Players(){
    this->TotalPlayers = 0;
    this->Winner = -1; // Winning player index
    this->MinPlayers = this->MaxPlayers = 2;
}

std::string Players::GetPlayerName(int PlayerIndex ){
    if (PlayerIndex < 0)
        PlayerIndex = 0;
    if(PlayerIndex < TotalPlayers)
        return PlayerList[PlayerIndex]->PlayerName;
    return "Invalid Index";
}

char Players::GetPlayerColor(int PlayerIndex){
    if (PlayerIndex < 0)
        PlayerIndex = 0;

    if(PlayerIndex < TotalPlayers)
        return PlayerList[PlayerIndex]->PlayerID;

    return 0;
}

int Players::AddPlayer(Player* P){
    //Create a copy of the player and place it at the end of Player List
    if(TotalPlayers >= MaxPlayers || P == nullptr)
        return -1;
//    PlayerList.push_back(  new Player(*P) );
    PlayerList.push_back(P);
    TotalPlayers++;
    return TotalPlayers;
}

