#include "game.h"
#include "board.cpp"
int main(int argc, char** argv)
{
    // Initialize the random number generator
    srand (time(NULL));

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Open a 800x600 window and define an accelerated renderer
    SDL_Window* window = SDL_CreateWindow("SDL2 & Code::Blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          490, 490, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    board field;

    // Initial renderer color


    bool running = true;
    SDL_Event event;
    while (running)
    {
        // Check for various events (keyboard, mouse, touch, close)
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                const char* key = SDL_GetKeyName(event.key.keysym.sym);
                if (strcmp(key, "Q") == 0 || strcmp(key, "Escape") == 0)
                {
                    running = false;
                }
            }
            else if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }


                SDL_Event event;
                SDL_SetRenderDrawColor(renderer,255,255,255,0);
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                for(int x=0;x<49;x++)
                {
                    for(int y=0;y<49;y++)
                    {
                        SDL_Rect box = {10*x,10*y,10,10};
                        if(x==5&&y==5)
                        {
                            SDL_RenderFillRect(renderer, &box);
                        }
                        else
                        {
                            SDL_RenderDrawRect(renderer, &box);
                        }
                    }
                }
                SDL_RenderPresent(renderer);

    }

    // Release any of the allocated resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
