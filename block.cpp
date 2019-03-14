#include "game.h"
using namespace std;
class block
{
    private:
        int x;
        int y;
        int z;
    public:
        block(int a, int b, int c)
        {
            x=a;
            y=b;
            z=c;
        }
        void updateX(int a)
        {
            x=a;
        }
        void updateY(int a)
        {
            y=a;
        }
        void updateZ(int a)
        {
            z=a;
        }
        void updateXYZ(int a, int b, int c)
        {
            x=a;
            y=b;
            z=c;
        }
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
