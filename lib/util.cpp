#include "util.hpp"

#include <SDL.h>

#include <stdexcept>

auto check_error(void *ptr, Error error) -> void {
	if (ptr == nullptr)
		throw std::runtime_error{error()};
}

auto check_error(int ret, Error error) -> void {
	if (ret < 0)
		throw std::runtime_error{error()};
}