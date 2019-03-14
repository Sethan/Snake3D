# Snake3D
The class block is just a 3D point
The class snake is a list of blocks, with the head being the pointer to the first block and tail being a pointer to the last. 
The lengt is the length of the snake. The method add() appends a block to the snake and sets the tail to the new block.
The method moveForward moves the head and makes the rest of the blocks follow the head. The method printsnake prints the entire snake.

The class board is a game board, consisting of a snake a threedimensional array, and an enum as direction.

The class main creates a window that renders an array with the size 49 and can fill them if a requirement is met.
