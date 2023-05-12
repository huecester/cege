#include "window.hpp"

#include <SDL.h>

#include "texture.hpp"
#include "util.hpp"

Window::Window(const WindowOptions &window_options)
	: window{initialize_window(window_options), SDL_DestroyWindow},
	  renderer{initialize_renderer(window.get(), window_options.renderer_flags), SDL_DestroyRenderer} {}

Window::~Window() {
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

auto Window::load_image(const std::filesystem::path &path) const -> Texture {
	return Texture{path, renderer.get()};
}

auto Window::initialize_window(const WindowOptions &window_options) -> SDL_Window * {
	check_error(SDL_InitSubSystem(SDL_INIT_VIDEO));

	auto window = SDL_CreateWindow(window_options.title, window_options.x, window_options.y, window_options.w, window_options.h, window_options.window_flags);
	check_error(window);
	return window;
}

auto Window::initialize_renderer(SDL_Window *window, Uint32 flags) -> SDL_Renderer * {
	auto renderer = SDL_CreateRenderer(window, -1, flags);
	check_error(renderer);
	return renderer;
}