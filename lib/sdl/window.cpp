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

auto Window::operator*() const -> SDL_Window * {
	return window.get();
}

auto Window::operator->() const -> SDL_Window * {
	return **this;
}

auto Window::get_renderer() const -> SDL_Renderer * {
	return renderer.get();
}

auto Window::load_image(const std::filesystem::path &path) const -> Texture {
	return Texture{path, renderer.get()};
}

auto Window::set_clear_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) -> void {
	SDL_SetRenderDrawColor(get_renderer(), r, g, b, a);
}

auto Window::clear() -> void {
	SDL_RenderClear(get_renderer());
}

auto Window::render(Texture &texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect, double angle, const SDL_Point *center, SDL_RendererFlip flip) -> void {
	SDL_RenderCopyEx(get_renderer(), *texture, srcrect, dstrect, angle, center, flip);
}

auto Window::present() -> void {
	SDL_RenderPresent(get_renderer());
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