#include "gamemove.h"

GameMove::GameMove(std::string Description){
    this->Description = Description;
}
std::string GameMove::toString(){
    return Description;
}
