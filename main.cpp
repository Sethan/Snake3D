#include "game.h"
#include "board.cpp"
int main(int argc, char** argv)
{
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    //Here the board object is created with the name field, the ints s and modifiers are given values based on the fields mapSize
    board field;
    int s=field.getMapSize();
    int modifier=512/s;

    // Opens a 512x512+modifier window and define an accelerated renderer
    SDL_Window* window = SDL_CreateWindow("SDL2 & Code::Blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          512, 512+modifier, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    //A boolean running set to true a SDL_Event and three Uint32 are used to create a running enviorment for the game,
    bool running = true;
    SDL_Event event;
    Uint32 old_time = 0, change_time = 200, new_time;
    while (running)
    {
        // Check for various events (keyboard, mouse, touch, close)
	//The button q quits the game. A W D S, is used to change directions
	// A in effect changes the direction 90 degrees anticlockwise and D changes the direction 90 degrees clockwise.
	// W and S sets the direction out and IN
	//If the x is pressed the game also quits
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                const char* key = SDL_GetKeyName(event.key.keysym.sym);
                if (strcmp(key, "Q") == 0 || strcmp(key, "Escape") == 0)
                {
                    running = false;
                }

                if (strcmp(key, "D") == 0)
                {
                    if(field.currentDirection==board::LEFT)
                    {
                        field.setDirectionDOWN();
                    }
                    else if(field.currentDirection==board::UP)
                    {
                        field.setDirectionLEFT();
                    }
                    else if(field.currentDirection==board::RIGHT)
                    {
                        field.setDirectionUP();
                    }
                    else
                    {
                        field.setDirectionRIGHT();
                    }
                }
                if (strcmp(key, "A") == 0)
                {
                    if(field.currentDirection==board::LEFT)
                    {
                        field.setDirectionUP();
                    }
                    else if(field.currentDirection==board::UP)
                    {
                        field.setDirectionRIGHT();
                    }
                    else if(field.currentDirection==board::RIGHT)
                    {
                        field.setDirectionDOWN();
                    }
                    else
                    {
                        field.setDirectionLEFT();
                    }
                }
                if (strcmp(key, "W") == 0)
                {
                    field.setDirectionOUT();
                }
                if (strcmp(key, "S") == 0)
                {
                    field.setDirectionIN();
                }
            }
            else if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }
	//New time is given the value of current ticks
	new_time = SDL_GetTicks();
	//If the difference between old time and new time is larger than change time then the game renders
	//first field.nextMove() is called to move the snake.
	//Then the snakemap is updated
	//Then the screen gets reset
	//A for looping over the mapSize (only in the x and y directions)
	//A SDL_Rect box is created with the posistions of x and y timed with the modifier (so that they are correctly placed on
	//screen) and given the widht and height equal to the modifier
	//if field at the x and y with the heads z posisiton detects a 1 (meaning snake) a filled rectangle with a random green color is drawn
	//if field at the x and y with the heads z posistion detects a 3 then an red square is drawn (as a symbol for the apple)
	//else then an empty black box is drawn
	//Then on the bottom of the screen a filled rectangle will be drawn if there is an apple at that z level with z=0 being most left and z=last being right
	//after the for loop a filled green rectangle will be drawn on the bottom symbolizing the current depth of the snakes head, most left meaning its not deep and most right meaning most deep
	//Lastly old_time is updated
	if(new_time - old_time > change_time)
        {
            field.nextMove();
            field.updateMap();
            SDL_Event event;
            SDL_SetRenderDrawColor(renderer,255,255,255,0);
            SDL_RenderClear(renderer);
            for(int x=0;x<s;x++)
            {
                for(int y=0;y<s;y++)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_Rect box = {modifier*x,modifier*y,modifier,modifier};
                    if(field.getMapState(x,y,field.getDepth())==1)
                    {
                        SDL_SetRenderDrawColor(renderer, rand()%40, rand()%150+25, rand()%40, 255);
                        SDL_RenderFillRect(renderer, &box);
                    }
                    else if(field.getMapState(x,y,field.getDepth())==3)
                    {
                        SDL_SetRenderDrawColor(renderer, rand()%150+100, 50, 50, 255);
                        SDL_RenderFillRect(renderer, &box);
                    }
                    else
                    {
                        SDL_RenderDrawRect(renderer, &box);
                    }
                    for(int z=0;z<s;z++)
                    {
                        if(field.getMapState(x,y,z)==3)
                        {
                            SDL_Rect bo2 = {z*modifier,512,modifier,modifier};
                            SDL_SetRenderDrawColor(renderer, rand()%150+100, 50, 50, 255);
                            SDL_RenderFillRect(renderer, &bo2);
                        }
                    }
                }
            }
            SDL_SetRenderDrawColor(renderer, rand()%40, rand()%150+25, rand()%40, 255);
            SDL_Rect box = {field.getDepth()*modifier,512,modifier,modifier};
            SDL_RenderFillRect(renderer, &box);
            SDL_RenderPresent(renderer);
            old_time = new_time;
        }
    }

    // Release any of the allocated resources when running=false
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
