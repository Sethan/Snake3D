#include <iostream>
#include <string>
using namespace std;
class snake
{
    private:
        block head;
        block tail;
        short int length;
        short int direction;
    public:
        createBody
        {
            this.head=new block(a,b,c,false);
            this.head.setNextBlock(new block(a,b+1,c,false));
            this.tail=this.head.getNextBlock().setNextBlock(new block(a,b+2,c,false));
        }
}
