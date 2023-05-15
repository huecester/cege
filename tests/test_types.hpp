#pragma once

#include <SDL.h>

#include "sdl/types.hpp"

constexpr WindowOptions TEST_WINDOW_OPTIONS{
	.title = "Hello, SDL!",
	.x = SDL_WINDOWPOS_CENTERED,
	.y = SDL_WINDOWPOS_CENTERED,
	.w = 640,
	.h = 480,
	.window_flags = SDL_WINDOW_SHOWN,
	.renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,
};
