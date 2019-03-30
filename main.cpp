#include "game.h"
#include "board.cpp"
int main(int argc, char** argv)
{
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Open a 800x600 window and define an accelerated renderer
    SDL_Window* window = SDL_CreateWindow("SDL2 & Code::Blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          490, 530, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    board field;


    bool running = true;
    SDL_Event event;
    Uint32 old_time = 0, change_color_time = 125, new_time;
    while (running)
    {
        // Check for various events (keyboard, mouse, touch, close)
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                const char* key = SDL_GetKeyName(event.key.keysym.sym);
                if (field.currentDirection==board::STOP)
                {
                    break;
                }
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

	    new_time = SDL_GetTicks();
	    if(new_time - old_time > change_color_time)
        {
            field.nextMove();
            field.updateMap();
            SDL_Event event;
            SDL_SetRenderDrawColor(renderer,255,255,255,0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            for(int x=0;x<49;x++)
            {
                for(int y=0;y<49;y++)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_Rect box = {10*x,10*y,10,10};
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
                }
            }

        SDL_RenderPresent(renderer);
        old_time = new_time;
        }


    }
    // Release any of the allocated resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
