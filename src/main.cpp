#include <SDL.h>

#include "context.hpp"
#include "sdl/texture.hpp"
#include "sdl/window.hpp"

constexpr auto WINDOW_TITLE = "Hello, SDL!";
constexpr auto WINDOW_WIDTH = 640;
constexpr auto WINDOW_HEIGHT = 480;

constexpr auto WINDOW_FLAGS = SDL_WINDOW_SHOWN;
constexpr auto RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

constexpr WindowOptions WINDOW_OPTIONS{WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS, RENDERER_FLAGS};

constexpr auto FIXED_TIMESTEP_MS = 1000 / 60;  // 60fps -> 1000 ms per 60 frames

int main() {
	Context ctx{WINDOW_OPTIONS};
	auto &window = ctx.get_window();

	auto rick = window.load_image("assets/rick_astley.png");

	SDL_Event e;
	bool quit = false;

	auto prev = SDL_GetTicks64();
	auto prev_fixed = prev;

	while (quit == false) {
		auto now = SDL_GetTicks64();

		// Fixed loop
		auto delta_fixed = now - prev_fixed;
		if (delta_fixed >= FIXED_TIMESTEP_MS) {
			// Fixed update
			// fixed_update_system->update(delta_fixed);
			prev_fixed += FIXED_TIMESTEP_MS;
		}

		// Variable loop/update
		auto delta = now - prev;
		prev = now;
		// update_system->update(delta);

		// Events
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) quit = true;
		}
	}
}