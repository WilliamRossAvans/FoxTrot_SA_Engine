#include "SVI.h"


SVI::SVI() 
{
    int audioFrequency = 44100;
    int audioChannelAmount = 2;
    int audioChunkSize = 2048;

	SDL_Init(SDL_INIT_EVERYTHING);
    //Initialize SDL_mixer
    if (Mix_OpenAudio(audioFrequency, MIX_DEFAULT_FORMAT, audioChannelAmount, audioChunkSize) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
	windowSDL2 = SDL_CreateWindow("Foxtrot Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	if (windowSDL2 == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}
    else
    {
        //Create renderer for window
        rendererSDL2 = SDL_CreateRenderer(windowSDL2, -1, SDL_RENDERER_ACCELERATED);
        if (rendererSDL2 == NULL)
        {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor(rendererSDL2, 0xFF, 0xFF, 0xFF, 0xFF);

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            }
        }
    }
}

SVI::~SVI()
{
	/*SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);*/
}