#pragma once

#include <SDL.h>

#include <filesystem>
#include <memory>

/// @brief A texture managed by SDL.
class Texture {
   public:
	/// @brief Load an image into a texture.
	/// @param path Path to the image.
	/// @param renderer The renderer to use.
	Texture(const std::filesystem::path &path, SDL_Renderer *renderer);

	/// @brief Get a pointer to the underlying `SDL_Texture`.
	/// @return A pointer to the `SDL_Texture` that this `Texture` manages.
	auto operator*() const -> SDL_Texture * {
		return texture.get();
	};

	/// @brief Get a pointer to the underlying `SDL_Texture`.
	/// @return A pointer to the `SDL_Texture` that this `Texture` manages.
	auto operator->() const -> SDL_Texture * {
		return **this;
	};

   private:
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;

	static auto initialize_texture(const std::filesystem::path &path, SDL_Renderer *renderer) -> SDL_Texture *;
};