#include <SDL.h>

void WindowEventLog(const SDL_Event * event);
void KeyboardEventLog(const SDL_Event * event);

void PrintEventLog(const SDL_Event * event)
{
	if (event->type == SDL_WINDOWEVENT) {
		WindowEventLog(event);
	}
	if (event->type == SDL_KEYDOWN) {
		KeyboardEventLog(event);
	}
}

void WindowEventLog(const SDL_Event * event)
{
	switch (event->window.event) {
		case SDL_WINDOWEVENT_SHOWN:
			SDL_Log("Window %d shown", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			SDL_Log("Window %d hidden", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_Log("Window %d exposed", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_MOVED:
			SDL_Log("Window %d moved to %d,%d",
					event->window.windowID, event->window.data1,
					event->window.data2);
			break;
		case SDL_WINDOWEVENT_RESIZED:
			SDL_Log("Window %d resized to %dx%d",
					event->window.windowID, event->window.data1,
					event->window.data2);
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			SDL_Log("Window %d size changed to %dx%d",
					event->window.windowID, event->window.data1,
					event->window.data2);
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			SDL_Log("Window %d minimized", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			SDL_Log("Window %d maximized", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_RESTORED:
			SDL_Log("Window %d restored", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_ENTER:
			SDL_Log("Mouse entered window %d",
					event->window.windowID);
			break;
		case SDL_WINDOWEVENT_LEAVE:
			SDL_Log("Mouse left window %d", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			SDL_Log("Window %d gained keyboard focus",
					event->window.windowID);
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			SDL_Log("Window %d lost keyboard focus",
					event->window.windowID);
			break;
		case SDL_WINDOWEVENT_CLOSE:
			SDL_Log("Window %d closed", event->window.windowID);
			break;
		default:
			SDL_Log("Window %d got unknown event %d",
					event->window.windowID, event->window.event);
			break;
	}
}

void KeyboardEventLog(const SDL_Event * event)
{
	switch (event->key.keysym.sym) {
		case SDLK_UP:
			SDL_Log("Physical UP key has been press down");
			break;
		case SDLK_DOWN:
			SDL_Log("Physical DOWN key has been press down");

			break;
		case SDLK_LEFT:
			SDL_Log("Physical LEFT key has been press down");
			break;
		case SDLK_RIGHT:
			SDL_Log("Physical RIGHT key has been press down");
			break;
		default:
			SDL_Log("Undefined key has been press down");
			break;
	}
}