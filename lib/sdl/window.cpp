#include "window.hpp"

#include <SDL.h>

#include "texture.hpp"
#include "util.hpp"

Window::Window(const char *title, int x, int y, int w, int h, Uint32 windowFlags, Uint32 rendererFlags)
	: window{initialize_window(title, x, y, w, h, windowFlags), SDL_DestroyWindow},
	  renderer{initialize_renderer(window.get(), rendererFlags), SDL_DestroyRenderer} {}

Window::~Window() {
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

auto Window::load_image(const std::filesystem::path &path) const -> Texture {
	return Texture{path, renderer.get()};
}

auto Window::initialize_window(const char *title, int x, int y, int w, int h, Uint32 flags) -> SDL_Window * {
	check_error(SDL_InitSubSystem(SDL_INIT_VIDEO));

	auto window = SDL_CreateWindow(title, x, y, w, h, flags);
	check_error(window);
	return window;
}

auto Window::initialize_renderer(SDL_Window *window, Uint32 flags) -> SDL_Renderer * {
	auto renderer = SDL_CreateRenderer(window, -1, flags);
	check_error(renderer);
	return renderer;
}