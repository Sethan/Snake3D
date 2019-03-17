#include "game.h"
#include "snake.cpp"
class board
{
    private:
        snake player;
        int snakemap[49][49][49];
        enum Direction{STOP, UP, DOWN, LEFT, RIGHT, IN, OUT};
        enum Plane{XY,XZ,YZ};
        Plane currentPlane;
    public:
        Direction currentDirection;
        board()
        {
            currentDirection=UP;
            currentPlane=XY;
        }
        void setDirectionUP()
        {
            currentDirection=UP;
            if(currentPlane==XZ)
            {
                currentPlane=XY;
            }
        }
        void setDirectionDOWN()
        {
            currentDirection=DOWN;
            if(currentPlane==XZ)
            {
                currentPlane=XY;
            }
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
            if(currentPlane==XY)
            {
                currentPlane=XZ;
            }
        }
        void setDirectionOUT()
        {
            currentDirection=OUT;
            if(currentPlane==XY)
            {
                currentPlane=XZ;
            }
        }
        void setPlaneXY()
        {
            currentPlane=XY;
        }
        void setPlaneXZ()
        {
            currentPlane=XZ;
        }
        void setPlaneYZ()
        {
            currentPlane=YZ;
        }
        bool checkPlaneXY()
        {
            return currentPlane==XY;
        }
        bool checkPlaneXZ()
        {
            return currentPlane==XZ;
        }
        bool checkPlaneYZ()
        {
            return currentPlane==YZ;
        }
        int getDepth()
        {
            if(currentPlane==XY)
            {
                return (*player.getHead()).getZ();
            }
            else if(currentPlane==XZ)
            {
                return (*player.getHead()).getY();
            }
            else
            {
                return (*player.getHead()).getX();
            }
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
            else if(currentDirection==IN)
            {
                z--;
            }
            else if(currentDirection==OUT)
            {
                z++;
            }
            if(getMapState(x,y,z)!=1&&!getOutOfBounds(x,y,z))
            {
                player.moveForward(x,y,z);
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
        bool getOutOfBounds(int x, int y, int z)
        {
            if(x<0||x>48||y<0||y>48||z<0||z>48)
            {
                return true;
            }
            return false;
        }
};

