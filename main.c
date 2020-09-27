#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Couldn't init video : %s", SDL_GetError());
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("Bald Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0); 

	if(window == NULL)
	{
		fprintf(stderr, "Couldn't create window: %s", SDL_GetError());
		return -1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


	int isRunning = 1;
	SDL_Event event;
	while(isRunning)
	{
		SDL_Delay(100);
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							isRunning = 0;
							break;
					}
					break;
				case SDL_QUIT:
					isRunning = 0;
					break;
			
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

}
