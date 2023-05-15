#pragma once

#include <SDL.h>

#include "sdl/types.hpp"
#include "sdl/window.hpp"

class Scene;

/// @brief Context for the application.
///
/// This class should be used to interface with various SDL functions.
/// It also contains the window for the application.
class Context {
   public:
	/// @brief Create a new context for an application.
	/// @param window_options Options to pass to `SDL_CreateWindow`.
	Context(const WindowOptions &window_options);

	~Context();

	/// @brief Get the current window.
	/// @return The current window.
	auto get_window() -> Window & { return window; };

	/// @brief Create a new scene with a managed ECS.
	/// @return A new scene.
	auto create_scene() -> Scene;

	Context(const Context &) = delete;
	Context(Context &&) = delete;
	auto operator=(const Context &) -> void = delete;

   private:
	Window window;
};