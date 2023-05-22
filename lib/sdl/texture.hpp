#pragma once

#include <SDL.h>

#include <filesystem>
#include <memory>

/// @brief A texture managed by SDL.
class Texture {
   public:
	/// @internal
	/// @brief Default constructor for a texture to allow it to be used as a component.
	Texture();

	/// @brief Load an image into a texture.
	/// @param path Path to the image.
	/// @param renderer The renderer to use.
	Texture(const std::filesystem::path &path, SDL_Renderer *renderer);

	/// @brief Get a pointer to the underlying `SDL_Texture`.
	/// @return A pointer to the `SDL_Texture` that this `Texture` manages.
	auto operator*() const -> SDL_Texture *;

	/// @brief Get a pointer to the underlying `SDL_Texture`.
	/// @return A pointer to the `SDL_Texture` that this `Texture` manages.
	auto operator->() const -> SDL_Texture *;

	/// @brief Get the width of the texture.
	/// @return The width of the texture.
	auto get_width() const -> int;

	/// @brief Get the height of the texture.
	/// @return The height of the texture.
	auto get_height() const -> int;

   private:
	std::shared_ptr<SDL_Texture> texture;
	int width, height;

	static auto initialize_texture(const std::filesystem::path &path, SDL_Renderer *renderer) -> SDL_Texture *;
};