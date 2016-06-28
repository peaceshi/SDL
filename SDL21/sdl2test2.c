#include "general.h"
#include <SDL.h>
#include "res_path.h"
#include "clean_up.h"

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
* Loads a BMP image into a texture on the rendering device
* @param file The BMP image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const char* file, SDL_Renderer *ren) {
	//Initialize to nullptr to avoid dangling pointer issues
	SDL_Texture *texture = NULL;
	//Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(file);
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != NULL) {
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Make sure converting went ok too
		if (texture == NULL) {
			logSDLError(stdout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(stdout, "LoadBMP");
	}
	return texture;
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
int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDLError(stdout, "SDL_Init");
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH,
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

	const char* resPath = getResourcePath("Lesson2");
	char bgPath[255], imgPath[255];
	strcpy(bgPath, resPath);
	sprintf(bgPath, "%s%s", bgPath, "background.bmp");

	strcpy(imgPath, resPath);
	sprintf(imgPath, "%s%s", imgPath, "image.bmp");
	// 	printf("%s\n%s\n", bgPath, imgPath);
	SDL_Texture *background = loadTexture(bgPath, renderer);
	SDL_Texture *image = loadTexture(imgPath, renderer);
	if (background == NULL || image == NULL) {
		cleanup("%t%t%r%w", background, image, renderer, window);
		Quit();
		return 1;
	}

	SDL_RenderClear(renderer);

	int bW, bH;
	SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
	renderTexture(background, renderer, 0, 0);
	renderTexture(background, renderer, bW, 0);
	renderTexture(background, renderer, 0, bH);
	renderTexture(background, renderer, bW, bH);

	int iW, iH;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;
	renderTexture(image, renderer, x, y);

	SDL_RenderPresent(renderer);
	SDL_Delay(1000);

	cleanup("%t%t%r%w", background, image, renderer, window);
	Quit();

	return 0;
}