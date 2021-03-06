#include "game.h"

using namespace std;

class block
{
    // The block class has three int data members, each representing a coordinate in a three dimensional plane.
    private:
        int x;
        int y;
        int z;
    public:
        // The constructor creates a block from three parameters, each giving x, y, and z a value.
        block(int a, int b, int c)
        {
            x = a;
            y = b;
            z = c;
        }

        // The following update methods update their corresponding data member's values.
        void updateX(int a)
        {
            x = a;
        }

        void updateY(int a)
        {
            y = a;
        }

        void updateZ(int a)
        {
            z = a;
        }

        void updateXYZ(int a, int b, int c)
        {
            x = a;
            y = b;
            z = c;
        }

        // The get methods return the int values of their corresponding data members.
        int getX()
        {
            return x;
        }

        int getY()
        {
            return y;
        }

        int getZ()
        {
            return z;
        }
};
