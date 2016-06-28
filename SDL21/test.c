#include <SDL.h>

#define SCREEN_W 800
#define SCREEN_H 600

int main(int argc, char **argv) {
	SDL_Window *pWindow = NULL;
	SDL_Renderer *pRenderer = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	pWindow = SDL_CreateWindow(
		"Geometry Rendering", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		SCREEN_W, SCREEN_H, 
		SDL_WINDOW_OPENGL |SDL_WINDOW_RESIZABLE);
	pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				quit = true;
		}
		SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(pRenderer);

		SDL_Rect fillRect = { SCREEN_W / 4, SCREEN_H / 4, SCREEN_W / 2, SCREEN_H / 2 };
		SDL_SetRenderDrawColor(pRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(pRenderer, &fillRect);       //填充矩形

		SDL_Rect outlineRect = { SCREEN_W / 6, SCREEN_H / 6, SCREEN_W * 2 / 3, SCREEN_H * 2 / 3 };
		SDL_SetRenderDrawColor(pRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(pRenderer, &outlineRect);     //绘制矩形边框

		SDL_SetRenderDrawColor(pRenderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderDrawLine(pRenderer, SCREEN_W * 4 / 5, SCREEN_H * 4 / 5, SCREEN_W * 1 / 5, SCREEN_H * 1 / 5);  //绘制线段

		SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0x00, 0xFF);
		for (int i = 0; i <= SCREEN_H; i += 10) {
			SDL_RenderDrawPoint(pRenderer, SCREEN_W / 2, i);    //绘制点
		}


		SDL_RenderPresent(pRenderer);
	}

	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();
	return 0;
}