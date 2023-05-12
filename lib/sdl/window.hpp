#pragma once

#include <SDL.h>

#include <filesystem>
#include <memory>

#include "types.hpp"

class Texture;

/// @brief A window/renderer pair managed by SDL.
class Window {
   public:
	/// @brief Window constructor.
	/// @param window_options Options to pass to `SDL_CreateWindow`.
	Window(const WindowOptions &window_options);

	~Window();

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

	/// @brief Load an image into a texture.
	/// @param path Path to the image.
	/// @return A texture containing the image.
	auto load_image(const std::filesystem::path &path) const -> Texture;

   private:
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;

	static auto initialize_window(const WindowOptions &window_options) -> SDL_Window *;
	static auto initialize_renderer(SDL_Window *window, Uint32 flags) -> SDL_Renderer *;
};