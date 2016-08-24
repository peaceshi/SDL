#include "general.h"
#include "res_path.h"
#include "clean_up.h"
#include "SDL_image.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(FILE* f, const char* msg) {
	fprintf(f, "%s%s\n", msg, SDL_GetError());
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const char* file, SDL_Renderer *ren) {
	SDL_Texture *texture = IMG_LoadTexture(ren, file);
	if (texture == NULL) {
		logSDLError(stdout, "LoadTexture");
	}
	return texture;
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
* width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param w The width of the texture to draw
* @param h The height of the texture to draw
*/
void renderTexture_Rect(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
// void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
// 	int w, h;
// 	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
// 	renderTexture(tex, ren, x, y, w, h);
// }

int main(int argc, char *argv[]) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDLError(stdout, "SDL_Init");
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError(stdout, "IMG_Init");
		Quit();
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Lesson 4", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		logSDLError(stdout, "CreateWindow");
		Quit();
		return 1;
	}


	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		logSDLError(stdout, "CreateRenderer");
		cleanup("%w", window);
		Quit();
		return 1;
	}

	const char* resPath = getResourcePath("Lesson4");
	char imgPath[255];

	strcpy(imgPath, resPath);
	sprintf(imgPath, "%s%s", imgPath, "image.png");
// 	printf("%s\n", imgPath);
	SDL_Texture *image = loadTexture(imgPath, renderer);
	if (image == NULL) {
		cleanup("%t%r%w", image, renderer, window);
		IMG_Quit();
		Quit();
		return 1;
	}
	// 	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	// 	for (int i = 0; i < 3; ++i) {

	int iW, iH;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;

	//Our event structure
	SDL_Event e;
	//For tracking if we want to quit
	bool quit = false;
	while (!quit) {
		//Read any events that occured, for now we'll just quit if any event occurs
		while (SDL_PollEvent(&e)) {
			//If user closes the window
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			//If user presses any key
			if (e.type == SDL_KEYDOWN) {
				quit = true;
			}
			//If user clicks the mouse
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				quit = true;
			}
		}
		//Rendering
		SDL_RenderClear(renderer);
		//Draw the image
		renderTexture(image, renderer, x, y);
		//Update the screen
		SDL_RenderPresent(renderer);
	}

	cleanup("%t%r%w", image, renderer, window);
	IMG_Quit();
	Quit();

	return 0;
}
