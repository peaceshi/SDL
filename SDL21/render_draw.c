#include <stdio.h>
#include <SDL.h>

void RenderCirclePlot(SDL_Renderer *renderer, int x0, int y0, int x, int y)
{
	SDL_Point points[8];
	points[0].x = x0 + x;
	points[0].y = y0 + y;
	points[1].x = x0 - x;
	points[1].y = y0 + y;
	points[2].x = x0 + x;
	points[2].y = y0 - y;
	points[3].x = x0 - x;
	points[3].y = y0 - y;
	points[4].x = x0 + y;
	points[4].y = y0 + x;
	points[5].x = x0 - y;
	points[5].y = y0 + x;
	points[6].x = x0 + y;
	points[6].y = y0 - x;
	points[7].x = x0 - y;
	points[7].y = y0 - x;
	if (SDL_RenderDrawPoints(renderer, points, 8)) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't RenderDrawPoints: %s", SDL_GetError());
	}
}//CirclePlot

void RenderFillCircle(SDL_Renderer *renderer, int x0, int y0, int r)
{
	int x, y, d;

	x = 0;
	y = r;
	d = 3 - 2 * r;
	RenderCirclePlot(renderer, x0, y0, x, y);

	while (x < y) {
		if (d < 0) {
			d = d + 4 * x + 6;
		}
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
		RenderCirclePlot(renderer, x0, y0, x, y);
		SDL_RenderDrawLine(renderer,
						   x0 - x, y0 - y,
						   x0 + x, y0 - y);
		SDL_RenderDrawLine(renderer,
						   x0 - x, y0 + y,
						   x0 + x, y0 + y);
		//
		SDL_RenderDrawLine(renderer,
						   x0 - y, y0 - x,
						   x0 + y, y0 - x);
		SDL_RenderDrawLine(renderer,
						   x0 - y, y0 + x,
						   x0 + y, y0 + x);
	}
	SDL_RenderDrawLine(renderer,
					   x0 - r, y0,
					   x0 + r, y0);
	SDL_RenderDrawLine(renderer,
					   x0, y0 - r,
					   x0, y0 + r);
}//RenderFillCircle

void RenderDrawCircle(SDL_Renderer *renderer, int x0, int y0, int r)
{
	int x, y, d;

	x = 0;
	y = r;
	d = 3 - 2 * r;
	RenderCirclePlot(renderer, x0, y0, x, y);

	while (x < y) {
		if (d < 0) {
			d = d + 4 * x + 6;
		}
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
		RenderCirclePlot(renderer, x0, y0, x, y);
	}
}//RenderDrawCircle

void RenderDrawTriangle(SDL_Renderer *renderer, int x0, int y0, int x1, int y1, int x2, int y2)
{
	SDL_Point point[4];
	point[0].x = x0;
	point[0].y = y0;
	point[1].x = x1;
	point[1].y = y1;
	point[2].x = x2;
	point[2].y = y2;
	point[3].x = x0;
	point[3].y = y0;

	if (SDL_RenderDrawLines(renderer, point, 4)) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't RenderDrawLines: %s", SDL_GetError());
	}

}//DrawTriangle

void RenderFillTriangle(SDL_Renderer *renderer, int x0, int y0, int x1, int y1, int x2, int y2)
{
	SDL_Point point[4];
	point[0].x = x0;
	point[0].y = y0;
	point[1].x = x1;
	point[1].y = y1;
	point[2].x = x2;
	point[2].y = y2;
	point[3].x = x0;
	point[3].y = y0;

	if (SDL_RenderDrawLines(renderer, point, 4)) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't RenderDrawLines: %s", SDL_GetError());
	}
	int xm = x1, xn = x0;
	if (x2 < x1 && x0 < x2) {
		xm = x2;
		for (xm, xn;xm <= x1, xn <= x2;xm++, xn++) {
			int ym = (int) (y2 - y1) / (x2 - x1)*xm + y1 - (y2 - y1) / (x2 - x1)*x1;
			int yn = (int) (y2 - y0) / (x2 - x0)*xn + y0 - (y2 - y0) / (x2 - x0)*x0;

			if (SDL_RenderDrawLine(renderer, xm, ym, xn, yn)) {
				SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't RenderDrawLine: %s", SDL_GetError());
			}
		}
	}
	if (x2 < x1 && x0 > x2) {
		xm = x2;
		xn = x2;
		for (xm, xn;xm <= x1, xn <= x0;xm++, xn++) {
			int ym = (int) (y2 - y1) / (x2 - x1)*xm + y1 - (y2 - y1) / (x2 - x1)*x1;
			int yn = (int) (y2 - y0) / (x2 - x0)*xn + y0 - (y2 - y0) / (x2 - x0)*x0;

			if (SDL_RenderDrawLine(renderer, xm, ym, xn, yn)) {
				SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't RenderDrawLine: %s", SDL_GetError());
			}
		}
	}
	if (x2 > x1 && x0 < x2) {
		for (xm, xn;xm <= x2, xn <= x2;xm++, xn++) {
			int ym = (int) (y2 - y1) / (x2 - x1)*xm + y1 - (y2 - y1) / (x2 - x1)*x1;
			int yn = (int) (y2 - y0) / (x2 - x0)*xn + y0 - (y2 - y0) / (x2 - x0)*x0;

			if (SDL_RenderDrawLine(renderer, xm, ym, xn, yn)) {
				SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't RenderDrawLine: %s", SDL_GetError());
			}
		}
	}
	if (x2 > x1 && x0 > x2) {
		xn = x2;
		for (xm, xn;xm <= x2, xn <= x0;xm++, xn++) {
			int ym = (int) (y2 - y1) / (x2 - x1)*xm + y1 - (y2 - y1) / (x2 - x1)*x1;
			int yn = (int) (y2 - y0) / (x2 - x0)*xn + y0 - (y2 - y0) / (x2 - x0)*x0;

			if (SDL_RenderDrawLine(renderer, xm, ym, xn, yn)) {
				SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't RenderDrawLine: %s", SDL_GetError());
			}
		}
	}

	// 	for (xm, xn;);
	// 	int ym =(int) (y2 - y1) / (x2 - x1)*xm +y1 - (y2 - y1) / (x2 - x1)*x1;
	// 	int yn = (int) (y2 - y0) / (x2 - x0)*xn + y0 -(y2 - y0) / (x2 - x0)*x0;
}//FillTriangle

void RenderDrawCoordinate(SDL_Renderer *renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, const float offset)
{
	float offset_lines = 0;
	float x1 = SCREEN_WIDTH*offset_lines, x2 = SCREEN_WIDTH*offset_lines, y1 = 0, y2 = SCREEN_HEIGHT;

	while (((SCREEN_WIDTH >= SCREEN_HEIGHT ? SCREEN_WIDTH : SCREEN_HEIGHT) >= x1)) {
		if (SCREEN_WIDTH >= x1) {
			if (SDL_RenderDrawLine(renderer, x1, y1, x2, SCREEN_HEIGHT)) {
				SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't RenderDrawLine: %s", SDL_GetError());
			}
		}
		if (SCREEN_HEIGHT >= x1) {
			if (SDL_RenderDrawLine(renderer, y1, x1, SCREEN_WIDTH, x2)) {
				SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't RenderDrawLine: %s", SDL_GetError());
			}
		}
		offset_lines = offset_lines + offset;
		x1 = SCREEN_WIDTH*offset_lines;
		x2 = SCREEN_WIDTH*offset_lines;
	}
}
