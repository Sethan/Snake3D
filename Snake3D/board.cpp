class board
{
    private:
        snake player;
        int dimensions=24;
        int snakemap[dimensions][dimensions][dimensions];
        enum Direction{STOP, UP, DOWN, LEFT, RIGHT, IN, OUT};
        Direction currentDirection=STOP;
    public:
        boardCreator
        {
            player=new snake(12,12,0);
        }
        setDirectionUP()
        {
            this.currentDirection=UP;
        }
        setDirectionDOWN()
        {
            this.currentDirection=DOWN;
        }
        setDirectionLEFT()
        {
            this.currentDirection=LEFT;
        }
        setDirectionRIGHT()
        {
            this.currentDirection=RIGHT;
        }
        setDirectionIN()
        {
            this.currentDirection=IN;
        }
        setDirectionOUT()
        {
            this.currentDirection=OUT;
        }

}
