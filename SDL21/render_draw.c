#include <stdio.h>
#include <SDL.h>
//https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
int SDL_GetIntersection_X(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int px = -1;
	int D = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
	if (D == 0) {
		return -2;
	}
	px = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4))
		/ (D);

	return px;
}

int SDL_GetIntersection_Y(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int py = -1;
	py = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4))
		/ ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));

	return py;
}

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

	//初始化(水平)扫描线端点
	const int scaner_x1 = ((point[0].x < point[1].x ? point[0].x : point[1].x) < point[2].x) ? (point[0].x < point[1].x ? point[0].x : point[1].x) : point[2].x;
	int scaner_y1 = ((point[0].y < point[1].y ? point[0].y : point[1].y) < point[2].y) ? (point[0].y < point[1].y ? point[0].y : point[1].y) : point[2].y;
	const int scaner_x2 = (point[0].x > point[1].x ? (point[0].x > point[2].x ? point[0].x : point[2].x) : point[1].x > point[2].x ? point[1].x : point[2].x);
	const int scaner_y2 = (point[0].y > point[1].y ? (point[0].y > point[2].y ? point[0].y : point[2].y) : point[1].y > point[2].y ? point[1].y : point[2].y);
// 	printf("scnner%d,%d,%d,%d\n", x1, x2, y1, y2);

//找出平行线
	int k = 0,m = -1;
	while (!(m == -2)) {
		k++;
		m = SDL_GetIntersection_X(scaner_x1, scaner_y1, scaner_x2, scaner_y1, point[0].x, point[0].y, point[k].x, point[k].y);
	}

	for (int i = 0;i < scaner_y2 - scaner_y1; ++i) {
		int x1 = -1, y1, x2, y2;
		switch (k) {
			case 1:
				x1 = SDL_GetIntersection_X(scaner_x1, scaner_y1 + i, scaner_x2, scaner_y1 + i, point[0].x, point[0].y, point[2].x, point[2].y);
				y1 = SDL_GetIntersection_Y(scaner_x1, scaner_y1 + i, scaner_x2, scaner_y1 + i, point[0].x, point[0].y, point[2].x, point[2].y);
				x2 = SDL_GetIntersection_X(scaner_x1, scaner_y1 + i, scaner_x2, scaner_y1 + i, point[1].x, point[1].y, point[2].x, point[2].y);
				y2 = SDL_GetIntersection_Y(scaner_x1, scaner_y1 + i, scaner_x2, scaner_y1 + i, point[1].x, point[1].y, point[2].x, point[2].y);
				break;
			case 2:
				x1 = SDL_GetIntersection_X(scaner_x1, scaner_y1 + i, scaner_x2, scaner_y1 + i, point[0].x, point[0].y, point[1].x, point[2].y);
				y1 = SDL_GetIntersection_Y(scaner_x1, scaner_y1 + i, scaner_x2, scaner_y1 + i, point[0].x, point[0].y, point[1].x, point[2].y);
				x2 = SDL_GetIntersection_X(scaner_x1, scaner_y1 + i, scaner_x2, scaner_y1 + i, point[1].x, point[1].y, point[2].x, point[2].y);
				y2 = SDL_GetIntersection_Y(scaner_x1, scaner_y1 + i, scaner_x2, scaner_y1 + i, point[1].x, point[1].y, point[2].x, point[2].y);
				break;
			case 3:
				x1 = SDL_GetIntersection_X(scaner_x1, scaner_y1 + i, scaner_x2, scaner_y1 + i, point[0].x, point[0].y, point[1].x, point[2].y);
				y1 = SDL_GetIntersection_Y(scaner_x1, scaner_y1 + i, scaner_x2, scaner_y1 + i, point[0].x, point[0].y, point[1].x, point[2].y);
				x2 = SDL_GetIntersection_X(scaner_x1, scaner_y1 + i, scaner_x2, scaner_y1 + i, point[0].x, point[0].y, point[2].x, point[2].y);
				y2 = SDL_GetIntersection_Y(scaner_x1, scaner_y1 + i, scaner_x2, scaner_y1 + i, point[0].x, point[0].y, point[2].x, point[2].y);
				break;
			default:
				printf("error!!\n");
				break;
		}
// 		printf("%d,%d,%d,%d\n", x1, y1, x2, y2);
		if (SDL_RenderDrawLine(renderer, x1, y1, x2, y2)){
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't RenderDrawLine: %s", SDL_GetError());
		}

	}

}//FillTriangle

// void RenderDrawCoordinate(SDL_Renderer *renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, const float offset)
// {
// 	float offset_lines = 0;
// 	float x1 = (SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH : SCREEN_HEIGHT)*offset_lines,
// 		x2 = (SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH : SCREEN_HEIGHT)*offset_lines,
// 		y1 = 0, y2 = SCREEN_HEIGHT;
// 
// 	while (((SCREEN_WIDTH > SCREEN_HEIGHT ? SCREEN_WIDTH : SCREEN_HEIGHT) >= x1)) {
// 		if (SCREEN_WIDTH >= x1) {
// 			if (SDL_RenderDrawLine(renderer, x1, y1, x2, SCREEN_HEIGHT)) {
// 				SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't RenderDrawLine: %s", SDL_GetError());
// 			}
// 		}
// 		if (SCREEN_HEIGHT >= x1) {
// 			if (SDL_RenderDrawLine(renderer, y1, x1, SCREEN_WIDTH, x2)) {
// 				SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't RenderDrawLine: %s", SDL_GetError());
// 			}
// 		}
// 		offset_lines += SCREEN_WIDTH/SCREEN_HEIGHT*offset;
// 		x1 = (SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH : SCREEN_HEIGHT)*offset_lines;
// 		x2 = (SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH : SCREEN_HEIGHT)*offset_lines;
// 	}
// }

