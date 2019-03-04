#include <iostream>
#include <string>
using namespace std;
class block
{
    private:
        short int x;
        short int y;
        short int z;
        bool edible;
        block* nBlock;
    public:
        blocker(short int a, short int b, short int c, bool t): this.x(a), this.y(b), this.z(c), this.edible(t){ }
        void updateX(short int a)
        {
            this.x=a;
        }
        void updateY(short int a)
        {
            this.y=a;
        }
        void updateZ(short int a)
        {
            this.z=a;
        }
        short int getX()
        {
            return this.x;
        }
        short int getY()
        {
            return this.y;
        }
        short int getZ()
        {
            return this.z;
        }
        bool getState()
        {
            return edible;
        }
        void setNext(block b)
        {
            this.nBlock=b;
        }

        block getNext()
        {
            return this.nBlock;
        }
}
