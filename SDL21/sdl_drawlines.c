#include "general.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;


int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Event event;
	bool quit = false;
	//��ʼ��SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
	}

	window = SDL_CreateWindow("SDL_DrawLines",
							  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  SCREEN_WIDTH, SCREEN_HEIGHT,
							  SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't CreateWindow: %s", SDL_GetError());
	}

	renderer = SDL_CreateRenderer(window, -1,
								  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't CreateRenderer: %s", SDL_GetError());
	}

	texture = SDL_CreateTexture(renderer,
								SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
								SCREEN_WIDTH, SCREEN_HEIGHT);
	if (texture == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't CreateTexture: %s", SDL_GetError());
	}
	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			PrintEventLog(&event);
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			if (event.type == SDL_WINDOWEVENT) {
				switch (event.window.event) {
					case SDL_WINDOWEVENT_SIZE_CHANGED: {
						//�����ڴ�С�仯ʱ�������ڿ��
						SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
						//δ�仯��������,���ٳ�����
						texture = SDL_CreateTexture(renderer,
													SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
													SCREEN_WIDTH, SCREEN_HEIGHT);
						if (texture == NULL) {
							SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't CreateTexture: %s", SDL_GetError());
						}
						break;
					}
				}
			}
			if (event.type == SDL_KEYDOWN) {
				//checks if a key is being remapped and prints what the remapping is
				if (event.key.keysym.scancode != SDL_GetScancodeFromKey(event.key.keysym.sym)) {
					SDL_Log("Physical %s key acting as %s key",
							SDL_GetScancodeName(event.key.keysym.scancode),
							SDL_GetKeyName(event.key.keysym.sym));
				}
			}
		}
		//������ȾĿ��
		if (SDL_SetRenderTarget(renderer, texture)) {
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't SetRenderTarget: %s", SDL_GetError());
		}
		if (SDL_SetRenderDrawColor(renderer, 50, 50, 50, 50)) {
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't SetRenderDrawColor: %s", SDL_GetError());
		}
		if (SDL_RenderClear(renderer)) {
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't RenderClear: %s", SDL_GetError());
		}
		if (SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255)) {
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't SetRenderDrawColor: %s", SDL_GetError());
		}
		if (SDL_RenderDrawLine(renderer,128,50,128,300))
		{
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't SetRenderDrawLine: %s", SDL_GetError());
		}
		if (SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255)) {
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't SetRenderDrawColor: %s", SDL_GetError());
		}
		if (SDL_RenderDrawLine(renderer, 128, 50, 420, 50)) {
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't SetRenderDrawLine: %s", SDL_GetError());
		}
// 		printf("%d , %d\n", SDL_GetIntersection_X(128, 50, 128, 300, 128, 50, 420, 50),
// 		SDL_GetIntersection_Y(128, 50, 128, 300, 128, 50, 420, 50));
// 		ֱ�ߵ�һ�㷽��ΪF(x) = ax + by + c = 0����Ȼ�����Ѿ�֪��ֱ�ߵ������㣬����Ϊ(x0, y0), (x1, y1)����ô���Եõ�a = y0 �C y1, b = x1 �C x0, c = x0y1 �C x1y0��
// 			������ǿ��Խ�����ֱ�߷ֱ��ʾΪ
// 			F0(x) = a0*x + b0*y + c0 = 0, F1(x) = a1*x + b1*y + c1 = 0
// 			��ô����ֱ�ߵĽ���Ӧ������
// 			a0*x + b0*y + c0 = a1*x + b1*y + c1
// 			�ɴ˿��Ƴ�
// 			x = (b0*c1 �C b1*c0) / D
// 			y = (a1*c0 �C a0*c1) / D
// 			D = a0*b1 �C a1*b0��(DΪ0ʱ����ʾ��ֱ���غ�)
		RenderFillTriangle(renderer, 128, 50,128, 450, 250, 500);
		SDL_SetRenderDrawColor(renderer, 0, 128, 232, 255);
		RenderDrawTriangle(renderer, 128, 50, 128, 450, 250, 500);
		RenderFillTriangle(renderer, 446, 50, 352, 450, 557, 500);
		SDL_SetRenderDrawColor(renderer,128, 128, 0, 255);
		RenderDrawTriangle(renderer, 446, 50, 352, 450, 557, 500);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	return 0;
}

