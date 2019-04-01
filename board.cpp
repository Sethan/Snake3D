#include "game.h"
#include "snake.cpp"

class board
{
    //The class board consists of the datamembers snake player
    //The player is a list over blocks that are meant to represent the snake logically, and used to update where the snake is in the array snakemap
    //The array snakemap is threedimensional and all the dimensions are given the values of mapSize. The state 0 in the map is used to represent empty space, 1 is the snake and 3 is the apple
    //mapSize can be changed to change the size of the board but should be given a value of 2^n to scale properly. (IE 8 16 32 64)
    //Int limit is the maximum amount of "apples" existing in the snakemap array
    //The int current is used to count the current amount of apples
    private:
        snake player;
        const static int mapSize=16;
        int snakemap[mapSize][mapSize][mapSize];
        int limit=5;
        int current=0;
    //The enum direction is a datatype used to keep track of which direction the snake is moving, STOP is unused and mostly used for troubleshooting purposes, UP and DOWN
    //makes the snake move along the y axis, left and right makes the snake move along the x axis, and lastly ZIN and ZOUT makes the snake move along the Z axis
    //currentDirection of type Direction is used to keep track of the direction.
    public:
        enum Direction{STOP, UP, DOWN, LEFT, RIGHT, ZIN, ZOUT};
        Direction currentDirection;
        //The constructor sets all the snakemap values to be equal to 0
        //The currentDirection is set to DOWN, the snake is moved one spot
        //Then apples are added to the snakemap
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
        //The setDirection methods are used to set the currentdirection to a specific direction
        //The getDirection method returns the currentDirection
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
        //The method getDepth returns the z value of the players head
        int getDepth()
        {
            return (*player.getHead()).getZ();
        }

        //The method next move copies the x y and z values of the head
        //And changes x y or z depending on the currentDirection
        //If the snakemap is empty in the new x y and z spot and its not out of bounds player.moveForward(x,y,z) is called
        //If the spot is occupied by an apple the player.add() is called then player.moveForward(x,y,z) is called current is decreased by one and addApple is called
        //If the spot is out of bounds or it is occupied by a part of the snake, Restart() is called

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
        //The method addApple loops over the distance between current and limit, and rolls three random numbers within the range of mapsize
        //If the random spot is empty an apple is added at that spot, if its not empty the for loop will loop one more time.
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
        //The method update map loops over the entire snakemap and if a spot is not occupied by an apple it is set to 0
        //Then the player is looped over and all the players posistions is used to set corrosponding snakemap posistions to 1
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
        //Int getMapState(x,y,z) returns the int value of snakemap[x][y][z] 0 meaning empty 1 meaning snake and 3 apple
        int getMapState(int x,int y,int z)
        {
            return snakemap[x][y][z];
        }
        //getOutOfBounds(x,y,z) checks if any of the ints are outside of the snakemap array and returns true if its outside
        bool getOutOfBounds(int x, int y, int z)
        {
            if(x<0||x>mapSize-1||y<0||y>mapSize-1||z<0||z>mapSize-1)
            {
                return true;
            }
            return false;
        }
        //getMapSize returns the mapSize
        int getMapSize()
        {
            return mapSize;
        }
        //Restart creates a new snake object replaces player with a copy of the new snake and deletes the new snake then currentDirection is set to RIGHT
        void Restart()
        {
            snake* newPlayer = new snake();
            player = *newPlayer;
            delete newPlayer;
            currentDirection=RIGHT;
        }
};

