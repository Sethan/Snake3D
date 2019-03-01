#include <iostream>
#include <string>
using namespace std;
class snake
{
    private:
        block head;
        block tail;
        short int length;
    public:
        createBody
        {
            this.head=new block(a,b,c,false);
            this.head.setNextBlock(new block(a,b+1,c,false));
            this.tail=this.head.getNextBlock().setNextBlock(new block(a,b+2,c,false));
            this.length=3;
        }
        void add()
        {
            short int a = this.tail.getX();
            short int b = this.tail.getY();
            short int c = this.tail.getZ();
            block t = new block(a,b,c,false);
            this.tail.setNext(t);
            this.tail=t;
            this.length++;
        }
        void moveForward(short int x, short int y, short int z)
        {
            block t = new block(x,y,z, false);
            t.setNext(this.head);
            this.head=t;
            block p=this.head;
            while(p.getNext().getNext()!=this.tail())
            {
                p=p.getNext();
            }
            t=this.tail();
            this.tail=p;
        }
}
