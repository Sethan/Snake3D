#include "game.h"
#include "snake.cpp"

class board
{
    // The class board contains the data member snake player.
    // The player is a list of blocks that are meant to represent the snake logically,
    // and used to update the snake's position in the array snakemap.
    // The array snakemap is three dimensional and all the dimensions are given the values of mapSize.
    // The state 0 in the map is used to represent an empty space, 1 is the snake, and 3 is an apple.
    // mapSize can be changed to change the size of the board,
    // but should be given a value of 2^n to scale properly. (IE 8 16 32 64)
    // Int limit is the maximum amount of "apples" existing in the snakemap array.
    // The int current is used to count the current amount of apples.
    private:
        snake player;
        const static int mapSize = 16;
        int snakemap[mapSize][mapSize][mapSize];
        int limit;
        int current;
        int tail;

    public:
        // The enum Direction is a data type used to keep track of which direction the snake is moving.
        // STOP is unused and mostly used for troubleshooting purposes.
        // UP and DOWN make the snake move along the y axis, LEFT and RIGHT make the snake move along the x axis,
        // and, lastly, ZIN and ZOUT make the snake move along the Z axis.
        // currentDirection of type Direction is used to keep track of the direction.
        enum Direction{STOP, UP, DOWN, LEFT, RIGHT, ZIN, ZOUT};
        Direction currentDirection;

        // The constructor sets all the snakemap values to be equal to 0.
        // The currentDirection is set to DOWN, the snake is moved one spot,
        // then, apples are added to the snakemap.
        board()
        {
            current = 0;
            limit = 5;
            for(int x = 0; x < mapSize; x++)
            {
                for(int y = 0; y < mapSize; y++)
                {
                    for(int z = 0; z < mapSize; z++)
                    {
                        snakemap[x][y][z] = 0;
                    }
                }
            }

            currentDirection = RIGHT;
            nextMove();
            addApple();
        }
        int getTail()
        {
            return tail;
        }
        // The setDirection methods are used to set the current direction to a specific direction.
        // The getDirection method returns the currentDirection.
        Direction getDirection()
        {
            return currentDirection;
        }

        void setDirectionUP()
        {
            currentDirection = UP;
        }

        void setDirectionDOWN()
        {
            currentDirection = DOWN;
        }

        void setDirectionLEFT()
        {
            currentDirection = LEFT;
        }

        void setDirectionRIGHT()
        {
            currentDirection = RIGHT;
        }

        void setDirectionIN()
        {
            currentDirection = ZIN;
        }

        void setDirectionOUT()
        {
            currentDirection = ZOUT;
        }

        // The method getDepth returns the z value of the player's head.
        int getDepth()
        {
            return (*player.getHead()).getZ();
        }

        // The method nextMove copies the x, y, and z values of the head
        // and changes x, y, or z depending on the currentDirection.
        // If the snakemap is empty in the new x, y, and z spot and it is not out of bounds,
        // player.moveForward(x, y, z) is called.
        // If the spot is occupied by an apple, player.add() is called, then player.moveForward(x, y, z)
        // is called, current is decreased by one, and addApple() is called.
        // If the spot is out of bounds or it is occupied by a part of the snake, Restart() is called.
        void nextMove()
        {
            int x = (*player.getHead()).getX();
            int y = (*player.getHead()).getY();
            int z = (*player.getHead()).getZ();

            if(currentDirection == LEFT)
            {
                x--;
            }
            else if(currentDirection == RIGHT)
            {
                x++;
            }
            else if(currentDirection == UP)
            {
                y++;
            }
            else if(currentDirection == DOWN)
            {
                y--;
            }
            else if(currentDirection == ZIN)
            {
                z--;
            }
            else if(currentDirection == ZOUT)
            {
                z++;
            }

            if(getMapState(x, y, z) == 0 && !getOutOfBounds(x, y, z))
            {
                player.moveForward(x, y, z);
            }
            else if(getMapState(x, y, z) == 3)
            {
                player.add();
                player.moveForward(x, y, z);
                current--;
                addApple();
            }
            else
            {
                Restart();
            }
        }

        // The method addApple loops over the distance between current and limit,
        // and rolls three random numbers within the range of mapSize.
        // If the random spot is empty, an apple is added at that spot, if it is not empty,
        // the for loop will loop one more time.
        void addApple()
        {
            for(int n = current; n < limit; n++)
            {
                int a = rand() % mapSize;
                int b = rand() % mapSize;
                int c = rand() % mapSize;

                if(snakemap[a][b][c] == 0)
                {
                    current++;
                    snakemap[a][b][c] = 3;
                }
                else
                {
                    n--;
                }
            }
        }

        // The method updateMap loops over the entire snakemap and if a spot is not occupied by an apple,
        // it is set to 0. Then, the player is looped over and all the player's positions are used
        // to set the corresponding snakemap positions to 1.
        void updateMap()
        {
            for(int x = 0; x < mapSize; x++)
            {
                for(int y = 0; y < mapSize; y++)
                {
                    for(int z = 0; z < mapSize; z++)
                    {
                        if(snakemap[x][y][z] != 3)
                        {
                           snakemap[x][y][z] = 0;
                        }
                    }
                }
            }
            int n=-1;
            for(block* p = player.getHead(); p < player.getTail() + 1; p++)
            {

                snakemap[(*p).getX()][(*p).getY()][(*p).getZ()] = n;
                n--;
            }
            tail=n+1;
        }

        // int getMapState(x, y, z) returns the int value of snakemap[x][y][z],
        // 0 meaning empty, 1 meaning snake, and 3 meaning apple.
        int getMapState(int x, int y, int z)
        {
            return snakemap[x][y][z];
        }

        // getOutOfBounds(x,y,z) checks if any of the parameters are outside the snakemap array
        // and returns true if it is outside.
        bool getOutOfBounds(int x, int y, int z)
        {
            if(x < 0 || x > mapSize - 1 || y < 0 || y > mapSize - 1 || z < 0 || z > mapSize - 1)
            {
                return true;
            }
            return false;
        }

        // getMapSize returns the mapSize
        int getMapSize()
        {
            return mapSize;
        }

        // Restart creates a new snake object, replaces player with a copy of the new snake,
        // and deletes the new snake. Then, currentDirection is set to RIGHT.
        void Restart()
        {
            snake* newPlayer = new snake();
            player = *newPlayer;
            delete newPlayer;
            currentDirection = RIGHT;
        }
};
