#include "texture.hpp"

#include <SDL.h>
#include <SDL_image.h>

#include "util.hpp"

Texture::Texture(const std::filesystem::path& path, SDL_Renderer* renderer)
	: texture{initialize_texture(path, renderer), SDL_DestroyTexture} {}

auto Texture::initialize_texture(const std::filesystem::path& path, SDL_Renderer* renderer) -> SDL_Texture* {
	auto texture = IMG_LoadTexture(renderer, path.c_str());
	check_error(texture, IMG_GetError);
	return texture;
}
