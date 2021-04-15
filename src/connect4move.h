#ifndef CONNECT4MOVE_H
#define CONNECT4MOVE_H
#include"gamemove.h"

class Connect4Move : public GameMove{
    public:
        Connect4Move(int Column = 0);
        int GetMove();
        bool SetMove(int Column);
    private:
        int Column;
};

#endif // CONNECT4MOVE_H

