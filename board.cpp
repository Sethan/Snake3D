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
        void nextMove()
        {
            int x=(*player.getHead()).getX();
            int y=(*player.getHead()).getY();
            int z=(*player.getHead()).getZ();
            if(currentDirection==LEFT)
            {
                player.moveForward(x-1,y,z);
            }
            else if(currentDirection==RIGHT)
            {
                player.moveForward(x+1,y,z);
            }
            else if(currentDirection==UP)
            {
                player.moveForward(x,y+1,z);
            }
            else if(currentDirection==DOWN)
            {
                player.moveForward(x,y-1,z);
            }
        }
        void updateMap()
        {
            for(int x=0;x<49;x++)
            {
                for(int y=0;y<49;y++)
                {
                    for(int z=0;z<49;z++)
                    {
                        snakemap[x][y][z]=0;
                    }
                }
            }

            for(block* p=player.getHead();p<player.getTail()+1;p++)
            {
                snakemap[(*p).getX()][(*p).getY()][(*p).getZ()]=1;
            }
            if(rand()%2==0)
            {
                player.add();
            }

        }
        int getMapState(int x,int y,int z)
        {
            return snakemap[x][y][z];
        }
};

