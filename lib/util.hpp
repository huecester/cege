#pragma once

#include <SDL.h>

#include <functional>

using Error = std::function<const char *()>;

/// @brief Helper function to convert an SDL result into an SDL value or throw.
/// @param ptr A (possibly null) pointer to an SDL resource.
/// @param error The SDL error function to use (SDL_GetError by default).
auto check_error(void *ptr, Error error = SDL_GetError) -> void;

/// @brief Helper function to convert an SDL result into an SDL value or throw.
/// @param ret An SDL return code, where 0 is a success and negative values are errors.
/// @param error The SDL error function to use (SDL_GetError by default).
auto check_error(int ret, Error error = SDL_GetError) -> void;