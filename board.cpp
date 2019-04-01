#include "game.h"
#include "snake.cpp"

class board
{
    private:
        snake player;
        const static int mapSize=16;
        int snakemap[mapSize][mapSize][mapSize];
        int limit=5;
        int current=0;
    public:
        enum Direction{STOP, UP, DOWN, LEFT, RIGHT, ZIN, ZOUT};
        Direction currentDirection;
        board()
        {
            for(int x=0;x<mapSize;x++)
            {
                for(int y=0;y<mapSize;y++)
                {
                    for(int z=0;z<mapSize;z++)
                    {
                        snakemap[x][y][z]=0;
                    }
                }
            }

            currentDirection=DOWN;
            nextMove();
            addApple();
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
            currentDirection=ZIN;
        }
        void setDirectionOUT()
        {
            currentDirection=ZOUT;
        }
        int getDepth()
        {
            return (*player.getHead()).getZ();
        }
        void nextMove()
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
            else if(currentDirection==ZIN)
            {
                z--;
            }
            else if(currentDirection==ZOUT)
            {
                z++;
            }
            if(getMapState(x,y,z)==0&&!getOutOfBounds(x,y,z))
            {
                player.moveForward(x,y,z);
            }
            else if(getMapState(x,y,z)==3)
            {
                player.add();
                player.moveForward(x,y,z);
                current--;
                addApple();
            }
            else
            {
                Restart();
            }
        }
        void addApple()
        {
            for(int n=current;n<limit;n++)
            {
                int a=rand()%mapSize;
                int b=rand()%mapSize;
                int c=rand()%mapSize;
                if(snakemap[a][b][c]==0)
                {
                    current++;
                    snakemap[a][b][c]=3;
                }
                else
                {
                    n--;
                }
            }
        }
        void updateMap()
        {
            for(int x=0;x<mapSize;x++)
            {
                for(int y=0;y<mapSize;y++)
                {
                    for(int z=0;z<mapSize;z++)
                    {
                        if(snakemap[x][y][z]!=3)
                        {
                           snakemap[x][y][z]=0;
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
            if(x<0||x>mapSize-1||y<0||y>mapSize-1||z<0||z>mapSize-1)
            {
                return true;
            }
            return false;
        }
        int getMapSize()
        {
            return mapSize;
        }
        void Restart()
        {
            snake* newPlayer = new snake();
            player = *newPlayer;
            delete newPlayer;
            currentDirection=RIGHT;
        }
};

