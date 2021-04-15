#ifndef CONNECT4STATE_H
#define CONNECT4STATE_H
#include"Connect4Move.h"
#include "gamestate.h"


class Connect4State : public GameState
{
    private:

        char State[6][7]; // A 6 x 7 array to hold discs placed by players
        int MoveTo[7]; // Hold largest empty row position for each column

        bool NoMoreMoves();
        int CheckWinner(int r, int c);

    protected:
        virtual double Utility(unsigned int PlayerIndex);
        void SetState(int r, int c, char ch);
        Connect4State(Connect4State& Connect4);

    public:
        Connect4State();
        char getState(int r, int c);
        virtual bool Winning(GameMove* Move);
        virtual bool Valid(GameMove* Move);
        virtual std::vector<GameMove*> GetPossibleMoves();
        virtual GameState* ApplyMove(GameMove* Move);
        virtual double EvaluateState(unsigned int PlayerIndex);
        virtual GameState* Clone();
};

#endif // CONNECT4STATE_H
