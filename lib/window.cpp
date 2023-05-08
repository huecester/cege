#include "window.hpp"

#include <SDL.h>

#include "util.hpp"

constexpr auto RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

Window::Window(const char *title, int x, int y, int w, int h, Uint32 windowFlags, Uint32 rendererFlags)
	: window{initialize_window(title, x, y, w, h, windowFlags), SDL_DestroyWindow},
	  renderer{initialize_renderer(rendererFlags), SDL_DestroyRenderer} {}

Window::~Window() {
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

auto Window::initialize_window(const char *title, int x, int y, int w, int h, Uint32 flags) -> SDL_Window * {
	check_error(SDL_InitSubSystem(SDL_INIT_VIDEO));

	auto window = SDL_CreateWindow(title, x, y, w, h, flags);
	check_error(window);
	return window;
}

auto Window::initialize_renderer(Uint32 flags) -> SDL_Renderer * {
	auto renderer = SDL_CreateRenderer(window.get(), -1, flags);
	check_error(renderer);
	return renderer;
}