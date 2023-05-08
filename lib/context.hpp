#pragma once

#include <SDL.h>

class Window;

/// @brief Context for the application. This class should be used to interface with various SDL functions.
class Context {
   public:
	/// @brief Get the context for the application.
	/// @return A reference to the context.
	static auto get_instance() -> Context &;

	/// @brief Create a window managed by SDL.
	/// @param title Title of the window.
	/// @param x X-position of the window, or `SDL_WINDOWPOS_CENTERED` or `SDL_WINDOWPOS_UNDEFINED`.
	/// @param y Y-position of the window, or `SDL_WINDOWPOS_CENTERED` or `SDL_WINDOWPOS_UNDEFINED`.
	/// @param w Width of the window.
	/// @param h Height of the window.
	/// @param windowFlags 0 or multiple `SDL_WindowFlags` OR'd together.
	/// @param rendererFlags 0 or multiple `SDL_RendererFlags` OR'd together.
	auto create_window(const char *title, int x, int y, int w, int h, Uint32 windowFlags, Uint32 rendererFlags) -> Window;

	~Context();

	Context(const Context &) = delete;
	Context(Context &&) = delete;
	auto operator=(const Context &) -> void = delete;

   private:
	Context();
};