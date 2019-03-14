#include "game.h"
#include "snake.cpp"
class board
{
    private:
        snake player;
        int snakemap[49][49][49];
        enum Direction{STOP, UP, DOWN, LEFT, RIGHT, IN, OUT};
        Direction currentDirection;
    public:

        board()
        {
            currentDirection=STOP;
            player.moveForward(10,10,0);
            player.moveForward(9,9,0);
            player.add();
            player.printsnake();
        }
        void setDirectionUP()
        {
            currentDirection=UP;
        }
        void setDirectionDOWN()
        {
            currentDirection=DOWN;
        }
        void setDirectionLEFT()
        {
            currentDirection=LEFT;
        }
        void setDirectionRIGHT()
        {
            currentDirection=RIGHT;
        }
        void setDirectionIN()
        {
            currentDirection=IN;
        }
        void setDirectionOUT()
        {
            currentDirection=OUT;
        }

};

