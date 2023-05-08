#pragma once

#include <SDL.h>

#include <filesystem>
#include <memory>

class Texture;

/// @brief A window/renderer pair managed by SDL.
class Window {
   public:
	/// @brief Window constructor.
	/// @param title Title of the window.
	/// @param x X-position of the window, or `SDL_WINDOWPOS_CENTERED` or `SDL_WINDOWPOS_UNDEFINED`.
	/// @param y Y-position of the window, or `SDL_WINDOWPOS_CENTERED` or `SDL_WINDOWPOS_UNDEFINED`.
	/// @param w Width of the window.
	/// @param h Height of the window.
	/// @param windowFlags 0 or multiple `SDL_WindowFlags` OR'd together.
	/// @param rendererFlags 0 or multiple `SDL_RendererFlags` OR'd together.
	Window(const char *title, int x, int y, int w, int h, Uint32 windowFlags, Uint32 rendererFlags);

	~Window();

	/// @brief Load an image into a texture.
	/// @param path Path to the image.
	/// @return A texture containing the image.
	auto load_image(const std::filesystem::path &path) const -> Texture;

	auto render_clear() const -> void {
		SDL_RenderClear(renderer.get());
	};

	auto render_copy(const Texture &texture) const -> void;

	auto render_present() const -> void {
		SDL_RenderPresent(renderer.get());
	}

	/// @brief Get a pointer to the underlying `SDL_Window`.
	/// @return A pointer to the `SDL_Window` that this `Window` manages.
	auto operator*() const -> SDL_Window * {
		return window.get();
	};

	/// @brief Get a pointer to the underlying `SDL_Window`.
	/// @return A pointer to the `SDL_Window` that this `Window` manages.
	auto operator->() const -> SDL_Window * {
		return **this;
	};

   private:
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;

	static auto initialize_window(const char *title, int x, int y, int w, int h, Uint32 flags) -> SDL_Window *;
	static auto initialize_renderer(SDL_Window *window, Uint32 flags) -> SDL_Renderer *;
};