#include "game.h"
#include "board.cpp"

int main(int argc, char** argv)
{
    // Initialize SDL.
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    // Here, the board object is created with the name field,
    // and the integers s and modifier are given values based on the field's map size.
    board field;
    int s = field.getMapSize();
    int modifier = 512 / s;

    // Open a 512+modifierx512 window and define an accelerated renderer.
    SDL_Window* window = SDL_CreateWindow("SDL2 & Code::Blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          512+modifier, 512, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //Loads all the images used by the program
    SDL_Surface *image = IMG_Load("head.png");
    SDL_Texture *snakehead = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("apple.png");
    SDL_Texture *apple = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("body.png");
    SDL_Texture *body = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("tail.png");
    SDL_Texture *tail = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("bent.png");
    SDL_Texture *bent = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("icon.png");
    SDL_Texture *icon = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("ground.png");
    SDL_Texture *ground = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("grass.png");
    SDL_Texture *grass = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("stone.png");
    SDL_Texture *stone = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = IMG_Load("bar.png");
    SDL_Texture *bar = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    cout<<IMG_GetError();
    // A boolean, running, set to true, an SDL_Event, and three Uint32s
    // are used to create a running environment for the game.
    bool running = true;
    SDL_Event event;
    Uint32 old_time = 0, change_time = 5, new_time;
    int framecounter=0;
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
	// First, field.nextMove() is called to move the snake. if framecounter is 10, then the framecounter is set back to 0
	// Then, the snakemap is updated.
	// Then, the screen gets reset.
	//And then the correct background is drawn according to the depth the snake is on
	// A for is declared to loop over the mapSize (only in the x and y directions).
	// if a negative value is found indicating that it is a snake piece, and then if its -1 the head is drawn and angled considering where the next snake part is or given the "icon" if its moving with the z axis, the using getTail() it sees if it is the tail, and then using the same logic as
	//for the head it angles the tail.
	//If the snakepart is neither the tail nor the head, a snake body part is drawn if the snake part is a corner a correctly angled snake piece is drawn if its not a corner part it draws a snake part and angles it.
	//Then it checks if an apple is at the plane and draws it if it is there.
	//The next part is uses yet another for loop to update the side bar, and sees if any apples are at the different levels and draws them in at the right height,
	//after the triple for loop a snake icon is drawn at the level the snake is located at
	// Lastly, old_time is updated.
        if(framecounter==10)
        {
            field.nextMove();
            framecounter=0;
        }
        if(new_time - old_time > change_time)
        {

            field.updateMap();
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderClear(renderer);

            if(field.getDepth()==0)
            {
                SDL_RenderCopy(renderer, grass, NULL, NULL);
            }
            else if(field.getDepth()==s-1)
            {
                SDL_RenderCopy(renderer, stone, NULL, NULL);
            }
            else
            {
                SDL_RenderCopy(renderer, ground, NULL, NULL);
            }

            SDL_Rect vstrect = {512, 0, 32, 512};
            SDL_RenderCopy(renderer, bar, NULL, &vstrect);
            for(int x = 0; x < s; x++)
            {
                for(int y = 0; y < s; y++)
                {
                    if(field.getMapState(x, y, field.getDepth()) < 0)
                    {
                        SDL_Rect dstrect = { modifier*x, modifier*y, modifier, modifier};
                        if(field.getMapState(x, y, field.getDepth()) == -1)
                        {
                            if(field.currentDirection == board::ZIN||field.currentDirection == board::ZOUT)
                            {
                                SDL_RenderCopy(renderer, icon, NULL, &dstrect);
                            }
                            else if(field.getMapState(x-1, y, field.getDepth())==-2)
                            {

                                SDL_RenderCopyEx(renderer, snakehead, NULL, &dstrect,90,NULL,SDL_FLIP_NONE);
                            }
                            else if(field.getMapState(x+1, y, field.getDepth())==-2)
                            {

                                SDL_RenderCopyEx(renderer, snakehead, NULL, &dstrect,270,NULL,SDL_FLIP_NONE);
                            }
                            else if(field.getMapState(x, y-1, field.getDepth())==-2)
                            {
                                SDL_RenderCopyEx(renderer, snakehead, NULL, &dstrect,180,NULL,SDL_FLIP_NONE);
                            }
                            else
                            {
                                SDL_RenderCopy(renderer, snakehead, NULL, &dstrect);
                            }
                        }
                        else if(field.getMapState(x, y, field.getDepth())==field.getTail())
                        {
                            int angle=180;
                            if(field.getMapState(x-1, y, field.getDepth())==field.getTail()+1)
                            {
                                angle=270;
                            }
                            else if(field.getMapState(x+1, y, field.getDepth())==field.getTail()+1)
                            {
                                angle=90;
                            }
                            else if(field.getMapState(x, y-1, field.getDepth())==field.getTail()+1)
                            {
                                angle=0;
                            }
                            SDL_RenderCopyEx(renderer, tail, NULL, &dstrect,angle,NULL,SDL_FLIP_NONE);
                        }
                        else
                        {
                            int previous=field.getMapState(x, y, field.getDepth())+1;
                            int next=field.getMapState(x, y, field.getDepth())-1;
                            if((field.getMapState(x-1, y, field.getDepth())==next&&field.getMapState(x+1, y, field.getDepth())==previous)||(field.getMapState(x-1, y, field.getDepth())==previous&&field.getMapState(x+1, y, field.getDepth())==next))
                            {
                                SDL_RenderCopyEx(renderer, body, NULL, &dstrect,90,NULL,SDL_FLIP_NONE);
                            }
                            else if((field.getMapState(x, y-1, field.getDepth())==next&&field.getMapState(x, y+1, field.getDepth())==previous)||(field.getMapState(x, y-1, field.getDepth())==previous&&field.getMapState(x, y+1, field.getDepth())==next))
                            {
                                SDL_RenderCopyEx(renderer, body, NULL, &dstrect,0,NULL,SDL_FLIP_NONE);
                            }
                            else if((field.getMapState(x, y-1, field.getDepth())==next&&field.getMapState(x+1, y, field.getDepth())==previous)||(field.getMapState(x, y-1, field.getDepth())==previous&&field.getMapState(x+1, y, field.getDepth())==next))
                            {
                                SDL_RenderCopyEx(renderer, bent, NULL, &dstrect,270,NULL,SDL_FLIP_NONE);
                            }
                            else if((field.getMapState(x, y+1, field.getDepth())==next&&field.getMapState(x+1, y, field.getDepth())==previous)||(field.getMapState(x, y+1, field.getDepth())==previous&&field.getMapState(x+1, y, field.getDepth())==next))
                            {
                                SDL_RenderCopyEx(renderer, bent, NULL, &dstrect,0,NULL,SDL_FLIP_NONE);
                            }

                            else if((field.getMapState(x, y-1, field.getDepth())==next&&field.getMapState(x-1, y, field.getDepth())==previous)||(field.getMapState(x, y-1, field.getDepth())==previous&&field.getMapState(x-1, y, field.getDepth())==next))
                            {
                                SDL_RenderCopyEx(renderer, bent, NULL, &dstrect,180,NULL,SDL_FLIP_NONE);
                            }

                            else if((field.getMapState(x, y+1, field.getDepth())==next&&field.getMapState(x-1, y, field.getDepth())==previous)||(field.getMapState(x, y+1, field.getDepth())==previous&&field.getMapState(x-1, y, field.getDepth())==next))
                            {
                                SDL_RenderCopyEx(renderer, bent, NULL, &dstrect,90,NULL,SDL_FLIP_NONE);
                            }
                        }
                    }
                    else if(field.getMapState(x, y, field.getDepth()) == 3)
                    {
                        SDL_Rect dstrect = { modifier*x, modifier*y, modifier, modifier};
                        SDL_RenderCopy(renderer, apple, NULL, &dstrect);
                    }

                    for(int z = 0; z < s; z++)
                    {
                        if(field.getMapState(x, y, z) == 3)
                        {
                            SDL_Rect dstrect = { 512,z * modifier, modifier, modifier};
                            SDL_RenderCopy(renderer, apple, NULL, &dstrect);
                        }
                    }
                }
            }
            SDL_Rect dstrect = {512,field.getDepth() * modifier, modifier, modifier};
            SDL_RenderCopy(renderer, icon, NULL, &dstrect);
            SDL_RenderPresent(renderer);
            old_time = new_time;
            framecounter++;
        }
    }

    // Release any of the allocated resources when running = false.
    SDL_DestroyTexture(snakehead);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
