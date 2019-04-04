#include "game.h"
#include "board.cpp"

int main(int argc, char** argv)
{
    // Initialize SDL.
    SDL_Init(SDL_INIT_VIDEO);

    // Here, the board object is created with the name field,
    // and the integers s and modifier are given values based on the field's map size.
    board field;
    int s = field.getMapSize();
    int modifier = 512 / s;

    // Open a 512x512+modifier window and define an accelerated renderer.
    SDL_Window* window = SDL_CreateWindow("SDL2 & Code::Blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          512, 512+modifier, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // A boolean, running, set to true, an SDL_Event, and three Uint32s
    // are used to create a running environment for the game.
    bool running = true;
    SDL_Event event;
    Uint32 old_time = 0, change_time = 200, new_time;

    while (running)
    {
        // Check for various events (keyboard, mouse, touch, close).
        // The button q quits the game. A W D S are used to change direction.
        // A in effect changes the direction 90 degrees anticlockwise and D changes the direction 90 degrees clockwise.
        // W and S set the direction out and in.
        // If the x is pressed, the game also quits.
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
                    if(field.currentDirection == board::LEFT)
                    {
                        field.setDirectionDOWN();
                    }
                    else if(field.currentDirection == board::UP)
                    {
                        field.setDirectionLEFT();
                    }
                    else if(field.currentDirection == board::RIGHT)
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
                    if(field.currentDirection == board::LEFT)
                    {
                        field.setDirectionUP();
                    }
                    else if(field.currentDirection == board::UP)
                    {
                        field.setDirectionRIGHT();
                    }
                    else if(field.currentDirection == board::RIGHT)
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

	// New time is given the value of current ticks.
	new_time = SDL_GetTicks();

	// If the difference between old_time and new_time is larger than change_time, then the game renders.
	// First, field.nextMove() is called to move the snake.
	// Then, the snakemap is updated.
	// Then, the screen gets reset.
	// A for is declared to loop over the mapSize (only in the x and y directions).
	// An SDL_Rect, box, is created with the positions of x and y times the modifier
	// (so that they are correctly placed on screen), and given the width and height equal to the modifier.
	// If field at the x and y with the head's z position detects a 1 (meaning snake),
	// a filled rectangle with a random green color is drawn.
	// If field at the x and y with the head's z position detects a 3 then an red square is drawn
	// (as a symbol for the apple)
	// Else, an empty black box is drawn.
	// Then, on the bottom of the screen, a filled rectangle will be drawn if there is an apple
	// at that z level, with z = 0 being most left and z = last being right.
	// After the for loop, a filled green rectangle will be drawn on the bottom
	// symbolizing the current depth of the snake's head, most left meaning it is not deep
	// and most right meaning most deep.
	// Lastly, old_time is updated.
	if(new_time - old_time > change_time)
        {
            field.nextMove();
            field.updateMap();
            SDL_Event event;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderClear(renderer);

            for(int x = 0; x < s; x++)
            {
                for(int y = 0; y < s; y++)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_Rect box = {modifier * x, modifier * y, modifier, modifier};

                    if(field.getMapState(x, y, field.getDepth()) == 1)
                    {
                        SDL_SetRenderDrawColor(renderer, rand() % 40, rand() % 150 + 25, rand() % 40, 255);
                        SDL_RenderFillRect(renderer, &box);
                    }
                    else if(field.getMapState(x, y, field.getDepth()) == 3)
                    {
                        SDL_SetRenderDrawColor(renderer, rand() % 150 + 100, 50, 50, 255);
                        SDL_RenderFillRect(renderer, &box);
                    }
                    else
                    {
                        SDL_RenderDrawRect(renderer, &box);
                    }

                    for(int z = 0; z < s; z++)
                    {
                        if(field.getMapState(x, y, z) == 3)
                        {
                            SDL_Rect box2 = {z * modifier, 512, modifier, modifier};
                            SDL_SetRenderDrawColor(renderer, rand() % 150 + 100, 50, 50, 255);
                            SDL_RenderFillRect(renderer, &box2);
                        }
                    }
                }
            }

            SDL_SetRenderDrawColor(renderer, rand() % 40, rand() % 150 + 25, rand() % 40, 255);
            SDL_Rect box = {field.getDepth() * modifier, 512, modifier, modifier};
            SDL_RenderFillRect(renderer, &box);
            SDL_RenderPresent(renderer);
            old_time = new_time;
        }
    }

    // Release any of the allocated resources when running = false.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
