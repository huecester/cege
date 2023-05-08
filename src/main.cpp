#include <SDL.h>

#include "context.hpp"
#include "sdl/texture.hpp"
#include "sdl/window.hpp"

constexpr auto WINDOW_TITLE = "Hello, SDL!";
constexpr auto WINDOW_WIDTH = 640;
constexpr auto WINDOW_HEIGHT = 480;

constexpr auto WINDOW_FLAGS = SDL_WINDOW_SHOWN;
constexpr auto RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

int main() {
	auto &ctx = Context::get_instance();
	auto window = ctx.create_window(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS, RENDERER_FLAGS);

	auto rick = window.load_image("assets/rick_astley.png");
	window.render_clear();
	window.render_copy(rick);
	window.render_present();

	SDL_Event e;
	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) quit = true;
		}
	}
}