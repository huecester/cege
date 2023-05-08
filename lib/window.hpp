#pragma once

#include <SDL.h>

#include <memory>

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

	/// @brief Get the underlying SDL_Window *.
	/// @return A pointer to the SDL_Window that this Window manages.
	auto operator*() const -> SDL_Window * {
		return window.get();
	};

	/// @brief Get the underlying SDL_Window*.
	/// @return A pointer to the SDL_Window that this Window manages.
	auto operator->() const -> SDL_Window * {
		return **this;
	};

   private:
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;

	auto initialize_window(const char *title, int x, int y, int w, int h, Uint32 flags) -> SDL_Window *;
	auto initialize_renderer(Uint32 flags) -> SDL_Renderer *;
};