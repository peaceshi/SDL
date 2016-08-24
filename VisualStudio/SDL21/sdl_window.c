#include "general.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int main(int argc, char *argv[])
{
	//��ʼ��SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
	}
	//��������
	SDL_Window * main_window = SDL_CreateWindow(
		"SDL_RenderDrawShapes",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (main_window == NULL) {
		fprintf(stderr, "CreateWindow failed: %s\n", SDL_GetError());
	}
	//������Ⱦ��
	SDL_Renderer * main_window_renderer = SDL_CreateRenderer(
		main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (main_window_renderer == NULL) {
		fprintf(stderr, "CreateRenderer failed: %s\n", SDL_GetError());
	}
	//�����¼�ѭ��
	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				quit = true;
		}

		//������Ⱦ��������ɫ
		if (SDL_SetRenderDrawColor(main_window_renderer, 50, 50, 50, 50)) {
			fprintf(stderr, "SetRenderDrawColor: %s\n", SDL_GetError());
		}
		if (SDL_RenderClear(main_window_renderer)) {
			fprintf(stderr, "SDL_RenderClear: %s\n", SDL_GetError());
		}

		//������Ⱦ����ɫ
		if (SDL_SetRenderDrawColor(main_window_renderer, 0xFF, 0xFF, 0xff, 0xFF)) {
			fprintf(stderr, "SetRenderDrawColor: %s\n", SDL_GetError());
		}
		//����Բ��
		RenderDrawCircle(main_window_renderer, 100, 100, 50);
		//������Ⱦ��
// 		RenderFillCircle(main_window_renderer, 400, 400, 200);
		//���Բ��
		RenderFillCircle(main_window_renderer, 100, 250, 50);

		//������Ⱦ����ɫ
		if (SDL_SetRenderDrawColor(main_window_renderer, 255, 0, 0, 255)) {
			fprintf(stderr, "SetRenderDrawColor: %s\n", SDL_GetError());
		}
		//��������
		SDL_Rect outLineRect = { 200,50,150,100 };
		//���ƾ���
		if (SDL_RenderDrawRect(main_window_renderer, &outLineRect)) {
			fprintf(stderr, "SetRenderDrawColor: %s\n", SDL_GetError());
		}
		//��������
		SDL_Rect fillRect = { 200,200,150,100 };
		//������
		if (SDL_RenderFillRect(main_window_renderer, &fillRect)) {
			fprintf(stderr, "SetRenderDrawColor: %s\n", SDL_GetError());
		}

		//������Ⱦ����ɫ
		if (SDL_SetRenderDrawColor(main_window_renderer, 0xFF, 0xFF, 0x00, 0xFF)) {
			fprintf(stderr, "SetRenderDrawColor: %s\n", SDL_GetError());
		}
		//���ƶ����
		for (int i = 400,j = 50; i <= 550,j <= 150; i += 3,j+=2) {
			
			if (SDL_RenderDrawPoint(main_window_renderer, i, j)) {
				fprintf(stderr, "RenderDrawPoint: %s\n", SDL_GetError());
			}
		}
		//�����߶�
		if (SDL_RenderDrawLine(main_window_renderer, 400, 200, 550, 300)) {
			fprintf(stderr, "RenderDrawPoint: %s\n", SDL_GetError());
		}

		//������Ⱦ����ɫ
		if (SDL_SetRenderDrawColor(main_window_renderer, 0x00, 0xFF, 0xFF, 0xFF)) {
			fprintf(stderr, "SetRenderDrawColor: %s\n", SDL_GetError());
		}
		//����������
		RenderDrawTriangle(main_window_renderer, 675, 50, 600, 150, 750, 150);
		RenderFillTriangle(main_window_renderer, 675, 50, 600, 150, 750, 150);

		SDL_RenderPresent(main_window_renderer);
// 		SDL_RenderCopy(main_window_renderer, main_window_renderer, NULL, NULL);
	}
	
	SDL_Quit();
	return 0;

}//main