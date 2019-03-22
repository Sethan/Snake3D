#include "game.h"
#include "snake.cpp"
class board
{
    private:
        snake player;
        int snakemap[49][49][49];
        int limit=1;
        int current=1;
        enum Direction{STOP, UP, DOWN, LEFT, RIGHT, IN, OUT};
    public:
        Direction currentDirection;
        board()
        {
            currentDirection=RIGHT;
            player.add();
            player.add();
            nextMove();
        }
        Direction getDirection()
        {
            return currentDirection;
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
        int getDepth()
        {
            return (*player.getHead()).getZ();
        }
        bool nextMove()
        {
            int x=(*player.getHead()).getX();
            int y=(*player.getHead()).getY();
            int z=(*player.getHead()).getZ();

            if(currentDirection==LEFT)
            {
                x--;
            }
            else if(currentDirection==RIGHT)
            {
                x++;
            }
            else if(currentDirection==UP)
            {
                y++;
            }
            else if(currentDirection==DOWN)
            {
                y--;
            }
            else if(currentDirection==IN)
            {
                z--;
            }
            else if(currentDirection==OUT)
            {
                z++;
            }
            if(getMapState(x,y,z)==0&&!getOutOfBounds(x,y,z))
            {
                player.moveForward(x,y,z);
                return true;
            }
            else if(getMapState(x,y,z)==3)
            {
                player.add();
                player.moveForward(x,y,z);
                current--;
                return true;
            }
            else
            {
                currentDirection=STOP;
                return false;
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
                        if(snakemap[x][y][z]!=3)
                        {
                           snakemap[x][y][z]=0;
                        }
                        if(z==getDepth())
                        {
                            if(current<limit)
                            {
                                current++;
                                cout<<current;
                                snakemap[rand()%49][rand()%49][z]=3;
                            }
                        }
                    }
                }
            }
            for(block* p=player.getHead();p<player.getTail()+1;p++)
            {
                snakemap[(*p).getX()][(*p).getY()][(*p).getZ()]=1;
            }
        }
        int getMapState(int x,int y,int z)
        {
            return snakemap[x][y][z];
        }
        bool getOutOfBounds(int x, int y, int z)
        {
            if(x<0||x>48||y<0||y>48||z<0||z>48)
            {
                return true;
            }
            return false;
        }
};

