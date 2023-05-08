#include "window.hpp"

#include <SDL.h>

#include "util.hpp"

Window::Window(const char *title, int x, int y, int w, int h, Uint32 flags) {
	check_error(SDL_InitSubSystem(SDL_INIT_VIDEO));

	window = SDL_CreateWindow(title, x, y, w, h, flags);
	check_error(window);
}

Window::~Window() {
	SDL_DestroyWindow(window);
}
