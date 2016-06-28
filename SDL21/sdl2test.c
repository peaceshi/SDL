#include "general.h"
#include "res_path.h"
#include "clean_up.h"

void logSDLError(FILE* f, const char* msg) {
	fprintf(f, "%s%s\n", msg, SDL_GetError());
}

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		// std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		logSDLError(stdout, "SDL_Init");
		return 1;
	}
	// 	std::cout << "Resource path is: " << getResourcePath() << std::endl;
// 	 	fprintf(stdout, "Resource path is: %s\n", getResourcePath());

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == NULL) {
		// 		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		fprintf(stdout, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL) {
		SDL_DestroyWindow(win);
		cleanup("%w", win);
		// 		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		fprintf(stdout, "SDL_CreateRenderer Error: %s\n", SDL_GetError());

		SDL_Quit();
		return 1;
	}

	// 	char* imagePath = getResourcePath("Lesson1") + "hello.bmp";
	char imagePath[255];
	strcpy(imagePath, getResourcePath("Lesson1"));
	sprintf(imagePath, "%s%s", imagePath, "hello.bmp");
	SDL_Surface *bmp = SDL_LoadBMP(imagePath);
	if (bmp == NULL) {
		// 		SDL_DestroyRenderer(ren);
		// 		SDL_DestroyWindow(win);
		cleanup("%r%w", ren, win);
		// 		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		fprintf(stdout, "SDL_LoadBMP Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == NULL) {
		// 		SDL_DestroyRenderer(ren);
		// 		SDL_DestroyWindow(win);
		cleanup("%r%w", ren, win);
		// 		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		fprintf(stdout, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());

		SDL_Quit();
		return 1;
	}

	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	for (int i = 0; i < 3; ++i) {
		//First clear the renderer
		SDL_RenderClear(ren);
		//Draw the texture
		SDL_RenderCopy(ren, tex, NULL, NULL);
		//Update the screen
		SDL_RenderPresent(ren);
		//Take a quick break after all that hard work
		SDL_Delay(1000);
	}

	system("pause");
	// 	SDL_DestroyTexture(tex);
	// 	SDL_DestroyRenderer(ren);
	// 	SDL_DestroyWindow(win);
	cleanup("%t%r%w", tex, ren, win);

	SDL_Quit();

	return 0;
}

