#include "general.h"
#include "res_path.h"
#include "clean_up.h"
#include "SDL_image.h"
#include <SDL_ttf.h>

//Screen attributes
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

/*
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param rend The renderer we want to draw too
* @param dst The destination rectangle to render the texture too
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip) {
	SDL_RenderCopy(ren, tex, clip, &dst);
}
/*
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height and taking a clip of the texture if desired
* If a clip is passed, the clip's width and height will be used instead of the texture's
* @param tex The source texture we want to draw
* @param rend The renderer we want to draw too
* @param x The x coordinate to draw too
* @param y The y coordinate to draw too
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void renderTexture_L(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != NULL) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	renderTexture(tex, ren, dst, clip);
}

void renderTexture_T(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	renderTexture(tex, ren, dst, NULL);
}

/*
* Render the message we want to display to a texture for drawing
* @param message The message we want to display
* @param fontFile The font we want to use to render the text
* @param color The color we want the text to be
* @param fontSize The size we want the font to be
* @param renderer The renderer to load the texture in
* @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
*/
SDL_Texture* renderText(const char** message, const char** fontFile, SDL_Color color,
	int fontSize, SDL_Renderer *renderer)
{
	//Open the font
	TTF_Font *font = TTF_OpenFont(fontFile, fontSize);
	if (font == NULL) {
		logSDLError(stdout, "TTF_OpenFont");
		return NULL;
	}
	//We need to first render to a surface as that's what TTF_RenderText returns, then
	//load that surface into a texture
	SDL_Surface *surf = TTF_RenderText_Blended(font, message, color);
	if (surf == NULL) {
		TTF_CloseFont(font);
		logSDLError(stdout, "TTF_RenderText");
		return NULL;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == NULL) {
		logSDLError(stdout, "CreateTexture");
	}
	//Clean up the surface and font
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

int main(int argc, char *argv[]) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDLError(stdout, "SDL_Init");
		return 1;
	}

	//Also need to init SDL_ttf
	if (TTF_Init() != 0) {
		logSDLError(stdout, "TTF_Init");
		SDL_Quit();
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Lesson 6", SDL_WINDOWPOS_CENTERED,
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

	const char* resPath = getResourcePath("Lesson6");
	char imgPath[255];

	strcpy(imgPath, resPath);
	sprintf(imgPath, "%s%s", imgPath, "sample.ttf");
	//We'll render the string "TTF fonts are cool!" in white
	//Color is in RGB format
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Texture *image = renderText("TTF fonts are cool!", imgPath, color, 64, renderer);

	// 	printf("%s\n", imgPath);
	if (image == NULL) {
		cleanup("%t%r%w", image, renderer, window);
		IMG_Quit();
		Quit();
		return 1;
	}
	//Get the texture w/h so we can center it in the screen
	int iW, iH;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		//Event Polling
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			}
		}
		SDL_RenderClear(renderer);
		//We can draw our message as we do any other texture, since it's been
		//rendered to a texture
		renderTexture_T(image, renderer, x, y);
		SDL_RenderPresent(renderer);
	}
	//Clean up
	cleanup("%t%r%w", image, renderer, window);
	IMG_Quit();
	Quit();

	return 0;
}
