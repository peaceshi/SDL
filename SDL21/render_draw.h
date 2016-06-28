#ifndef RENDER_DRAW_H
#define RENDER_DRAW_H
#include <SDL.h>

extern void RenderCirclePlot(SDL_Renderer *renderer, int x0, int y0, int x, int y);
//Bresenham_Circle
extern void RenderFillCircle(SDL_Renderer *renderer, int x0, int y0, int r);
extern void RenderDrawCircle(SDL_Renderer *renderer, int x0, int y0, int r);
extern void RenderDrawTriangle(SDL_Renderer *renderer, int x0, int y0, int x1, int y1, int x2, int y2);
extern void RenderFillTriangle(SDL_Renderer *renderer, int x0, int y0, int x1, int y1, int x2, int y2);

/**
*  \brief ���ƴ��ڲο���,�̶�����,����Ӧ���ڱ仯
*/
extern void RenderDrawCoordinate(SDL_Renderer * renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, float offset);

#endif // !RENDER_DRAW_H
