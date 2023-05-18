#pragma once

#include <SDL.h>

/// @brief Options to pass to `SDL_CreateWindow`.
struct WindowOptions {
	/// @brief Title of the window.
	const char *title;

	/// @brief X-position of the window, or `SDL_WINDOWPOS_CENTERED` or `SDL_WINDOWPOS_UNDEFINED`.
	int x;

	/// @brief Y-position of the window, or `SDL_WINDOWPOS_CENTERED` or `SDL_WINDOWPOS_UNDEFINED`.
	int y;

	/// @brief Width of the window.
	int w;

	/// @brief Height of the window.
	int h;

	/// @brief 0 or multiple `SDL_WindowFlags` OR'd together (SDL_WINDOW_SHOWN by default).
	Uint32 window_flags = SDL_WINDOW_SHOWN;

	/// @brief 0 or multiple `SDL_RendererFlags` OR'd together (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC by default).
	Uint32 renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
};
