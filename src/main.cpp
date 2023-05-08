#include <SDL.h>

#include "context.hpp"
#include "window.hpp"

constexpr auto WINDOW_TITLE = "Hello, SDL!";
constexpr auto WINDOW_WIDTH = 640;
constexpr auto WINDOW_HEIGHT = 480;

constexpr auto WINDOW_FLAGS = SDL_WINDOW_SHOWN;
constexpr auto RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

int main() {
	auto &ctx = Context::get_instance();
	auto window = ctx.create_window(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS, RENDERER_FLAGS);

	auto sdl_window = *window;
	auto surface = SDL_GetWindowSurface(sdl_window);
	SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0xff, 0xff, 0xff));
	SDL_UpdateWindowSurface(sdl_window);
	SDL_Event e;
	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) quit = true;
		}
	}
}