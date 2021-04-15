#include "gamestate.h"

//Players GamePlayers;

std::string GameState::GetPlayerName(int PlayerIndex){
    return GamePlayers.GetPlayerName(PlayerIndex);
}
char GameState::GetPlayerColor(int PlayerIndex){
    return GamePlayers.GetPlayerColor(PlayerIndex);
}

int GameState::AddPlayer(Player* P){
    return GamePlayers.AddPlayer(P);
}

double GameState::Utility(unsigned int PlayerIndex){
    return 0;
}

unsigned int GameState::GetTurningPlayer(){
    return TurningPlayer;
}

int GameState::WhoWon(){
    return this->GamePlayers.Winner;
}

GameState::GameState(){
    this->TurningPlayer = 0;  //index of player making the move
}

bool GameState::GameOver() {
    return (this->GamePlayers.Winner != -1);
}


bool GameState::MakeMove(){
    GameMove* Move = nullptr;
    Move = GamePlayers.PlayerList[TurningPlayer]->SuggestMove( Clone() );
    int NextTurn = SelectNextPlayer();
    if (!Valid(Move)){
        TurningPlayer = NextTurn;
        return false;
    }
    Winning(Move);
    ApplyMove(Move);
//            TurningPlayer = NextTurn;
    return true;
};

unsigned int GameState::SelectNextPlayer(){
    return (TurningPlayer + 1) % this->GamePlayers.TotalPlayers;
}

double GameState::EvaluateState(unsigned int PlayerIndex){
    return 0;
}
