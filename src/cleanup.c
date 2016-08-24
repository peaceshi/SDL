#include <stdarg.h>
#include <SDL.h>

void cleanup(char* fmt, ...)
{
	va_list ap;
	char flag;
	void *win, *ren, *tex, *surf;
	va_start(ap, fmt);
	while (*fmt) {
		flag = *fmt++;
		if ((int)flag != '%') {
			continue;
		}
		flag = *fmt++;

		switch ((int)flag) {
		case 't':
			win = va_arg(ap, SDL_Window *);
			SDL_DestroyWindow(win);
			break;
		case 'r':
			ren = va_arg(ap, SDL_Renderer *);
			SDL_DestroyRenderer(ren);
			break;
		case 'w':
			tex = va_arg(ap, SDL_Texture *);
			SDL_DestroyTexture(tex);
			break;
		case 's':
			surf = va_arg(ap, SDL_Surface *);
			SDL_FreeSurface(surf);
			break;
		}
	}
	va_end(ap);
}//cleanup