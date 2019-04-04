#include "game.h"
#include "block.cpp"

using namespace std;

class snake
{
    // The snake class consists of a block pointer, head, pointing to a block,
    // and a block pointer, tail, pointing to a block. Head points to an empty memory area
    // with space for three blocks, tail has a memory value of head + 2.
    // The int length's purpose is to show the length of the snake.
    // The snake itself serves as a list of blocks.
    private:
        block* head = (block*)malloc(sizeof(block) * 3);
        block* tail = head + 2;
        short int length;
    public:
        // The constructor takes no arguments and creates three blocks and assigns the head pointer
        // to point to the first block, and a temporary p pointer to point to the next block.
        // p is given the address of head + 1, then tail is also assigned to point to a new block.
        // The blocks are given values that put them in a corner one after another.
        // Length is given the correct value of 3.
        snake()
        {
            *head = block(0, 2, 0);
            block* p = head + 1;
            *p = block(0, 1, 0);
            *tail = block(0, 0, 0);
            length = 3;
        }

        // The method add uses the coordinates of the tail and the second to last block in the snake
        // to calculate three new coordinates.
        // head is set to pointed to a new memory spot with enough space for one more block.
        // Tail is given the value of head + length, which is an unused memory address,
        // then, tail's address is given the value of a new block with the coordinates calculated in the start.
        // Lastly, length is increased.
        void add()
        {
            int a = 2 * (*tail).getX() - (*(tail - 1)).getX();
            int b = 2 * (*tail).getY() - (*(tail - 1)).getY();
            int c = 2 * (*tail).getZ() - (*(tail - 1)).getZ();
            head = (block*)realloc(head, (length + 1) * sizeof(block));
            tail = head + length;
            *tail = block(a, b, c);
            length++;
        }

        // The method moveForward takes three parameters, x, y, and z.
        // The x y z values of head are copied over to a, b, and c.
        // head is then updated with x, y, and z. Looping over the snake object using pointers,
        // each snake block is given the coordinates of the block before it,
        // so p2 is given the coordinates of p1. This is achieved by copying the x y z to a1, b1, and c1,
        // and then setting x, y, and z to a b c, and replacing a b c with a1, b1, and c1.
        void moveForward(int x, int y, int z)
        {
            int a = (*head).getX();
            int b = (*head).getY();
            int c = (*head).getZ();

            (*head).updateXYZ(x, y, z);

            for(block* p = head + 1; p < tail + 1; p++)
            {
                int a1 = (*p).getX();
                int b1 = (*p).getY();
                int c1 = (*p).getZ();

                (*p).updateXYZ(a, b, c);

                a = a1;
                b = b1;
                c = c1;
            }
        }

        // The method PrintPosition prints out all the blocks' positions by looping over the snake object.
        // This method is used for troubleshooting.
        void PrintPosition()
        {
            for(block* p = head; p < tail + 1; p++)
            {
                cout << (*p).getX() << (*p).getY() << (*p).getZ() << "\n";
            }
        }

        // The last three methods return the data members of snake.
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
