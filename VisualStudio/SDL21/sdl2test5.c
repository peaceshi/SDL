#include "general.h"
#include "res_path.h"
#include "clean_up.h"
#include "SDL_image.h"

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

/*
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param rend The renderer we want to draw too
* @param dst The destination rectangle to render the texture too
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void renderTexture_T(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip) {
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
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip) {
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
	renderTexture_T(tex, ren, dst, clip);
}

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

	SDL_Window *window = SDL_CreateWindow("Lesson 5", SDL_WINDOWPOS_CENTERED,
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

	const char* resPath = getResourcePath("Lesson5");
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
	//iW and iH are the clip width and height
	//We'll be drawing only clips so get a center position for the w/h of a clip
	int iW = 100, iH = 100;
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;

	//Setup the clips for our image
	SDL_Rect clips[4];
	//Since our clips our uniform in size we can generate a list of their
	//positions using some math (the specifics of this are covered in the lesson)
	for (int i = 0; i < 4; ++i) {
		clips[i].x = i / 2 * iW;
		clips[i].y = i % 2 * iH;
		clips[i].w = iW;
		clips[i].h = iH;
	}
	//Specify a default clip to start with
	int useClip = 0;

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		//Event Polling
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			//Use number input to select which clip should be drawn
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_1:
				case SDLK_KP_1:
					useClip = 0;
					break;
				case SDLK_2:
				case SDLK_KP_2:
					useClip = 1;
					break;
				case SDLK_3:
				case SDLK_KP_3:
					useClip = 2;
					break;
				case SDLK_4:
				case SDLK_KP_4:
					useClip = 3;
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
			}
		}
		//Rendering
		SDL_RenderClear(renderer);
		//Draw the image
		renderTexture(image, renderer, x, y, &clips[useClip]);
		//Update the screen
		SDL_RenderPresent(renderer);
	}
	//Clean up
	cleanup("%t%r%w", image, renderer, window);
	IMG_Quit();
	Quit();

	return 0;
}
