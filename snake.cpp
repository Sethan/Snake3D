#include "game.h"
#include "block.cpp"

using namespace std;

class snake
{
    private:
        block* head=(block*) malloc(sizeof(block)*3);
        block* tail=head+2;
        short int length;
    public:
        snake()
        {
            *head= block(0,2,0);
            block* p=head+1;
            *p= block(0,1,0);
            *tail= block(0,0,0);
            length=3;
        }
        void add()
        {
            int a=2*(*tail).getX()-(*(tail-1)).getX();
            int b=2*(*tail).getY()-(*(tail-1)).getY();
            int c=2*(*tail).getZ()-(*(tail-1)).getZ();
            head = (block *)realloc(head, (length+1) * sizeof(block));
            tail = head+length;

            *tail= block(a,b,c);
            length++;
        }
        void moveForward(int x,int y,int z)
        {
            int a = (*head).getX();
            int b = (*head).getY();
            int c = (*head).getZ();
            (*head).updateXYZ(x,y,z);
            for(block* p=head+1;p<tail+1;p++)
            {
                int a1 = (*p).getX();
                int b1 = (*p).getY();
                int c1 = (*p).getZ();
                (*p).updateXYZ(a,b,c);
                a=a1;
                b=b1;
                c=c1;
            }
        }

        void PrintPosition()
        {
            for(block* p=head;p<tail+1;p++)
            {
                cout<<(*p).getX()<<(*p).getY()<<(*p).getZ()<<"\n";
            }
        }
        block* getHead()
        {
            return head;
        }
        block* getTail()
        {
            return tail;
        }
        short int getLength()
        {
            return length;
        }
};
