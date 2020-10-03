#include <SDL2/SDL.h>
#include <complex.h>
#include <assert.h>

struct Color
{
	int palette[10 + 1][3];
};

void color_init(struct Color *color)
{
	for (int i = 0; i <= 10; ++i)
	{
		color->palette[i][0] = i < 2 * 10 / 3 ? i * 255 * 3 / (2 * 10) : 255;
		color->palette[i][1] = i < 10 / 3 ? 0 : (i - 10 / 3) * 255 * 3 / (2 * 10);
		color->palette[i][2] = 0;
	}

}


//awful function that takes all of the cpu
void render_mandelbrot(SDL_Renderer* renderer, struct Color color)
{
	assert(color.palette != NULL); 

	double complex c, z;

	int a = 0;

	SDL_SetRenderDrawColor(renderer, 255,0,0, 255);
	for(unsigned int y=0;y<1000;++y)
	{
		for(unsigned int x=0;x<1000;++x)
		{
			c = CMPLX(0.5 * (x - (500 - 500) / 2) / 500 * 4.0 - 2.0, 0.5 * y / 500 * 4.0 - 2.0);
			z = CMPLX(0.0, 0.0);

			for(unsigned int cnt=0;cnt< 50;++cnt)
			{
				z = z * z + c;
				if(abs(z) > 2.0)
				{
					a = cnt;
					break;	
				}
			}

			SDL_SetRenderDrawColor(renderer, color.palette[a][0], color.palette[a][1], color.palette[a][2], 0xff);
			SDL_RenderDrawPoint(renderer, x, y);

		}
	}
}

int main(int argc, char **argv)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Couldn't init video : %s", SDL_GetError());
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("Another Mandelbrot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0); 

	if(window == NULL)
	{
		fprintf(stderr, "Couldn't create window: %s", SDL_GetError());
		return -1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	struct Color color;
	color_init(&color);

	int isRunning = 1;
	SDL_Event event;
	while(isRunning)
	{
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
	
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		render_mandelbrot(renderer, color);
		SDL_Delay(1000);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

}
