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
	auto operator*() const -> SDL_Window *;

	/// @brief Get a pointer to the underlying `SDL_Window`.
	/// @return A pointer to the `SDL_Window` that this `Window` manages.
	auto operator->() const -> SDL_Window *;

	/// @brief Get a pointer to the associated `SDL_Renderer`.
	/// @return A pointer to the `SDL_Renderer` that this `Window` manages.
	auto get_renderer() const -> SDL_Renderer *;

	/// @brief Load an image into a texture.
	/// @param path Path to the image.
	/// @return A texture containing the image.
	auto load_image(const std::filesystem::path &path) const -> Texture;

	/// @brief Set the clear color for the attached renderer.
	auto set_clear_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff) -> void;

	/// @brief Clear the attached renderer.
	auto clear() -> void;

	/// @brief Copy a texture to the renderer.
	/// @param texture The texture to copy.
	/// @param srcrect The source rect to copy from, or nullptr for the entire texture (nullptr by default).
	/// @param dstrect The destination rect to copy to, or nullptr for the entire texture (nullptr by default).
	/// @param angle The angle to rotate dstrect by clockwise (0.0 by default).
	/// @param center The center of rotation, or nullptr for the center of dstrect (nullptr by default).
	/// @param flip Which axes to flip dstrect around (none by default).
	auto render(Texture &texture, const SDL_Rect *srcrect = nullptr, const SDL_Rect *dstrect = nullptr, double angle = 0.0, const SDL_Point *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) -> void;

	/// @brief Update the window and swap the buffers.
	auto present() -> void;

   private:
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;

	static auto initialize_window(const WindowOptions &window_options) -> SDL_Window *;
	static auto initialize_renderer(SDL_Window *window, Uint32 flags) -> SDL_Renderer *;
};