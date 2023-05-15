#include "context.hpp"

#include <SDL_image.h>

#include <utility>

#include "ecs/scene.hpp"
#include "sdl/types.hpp"
#include "sdl/util.hpp"
#include "sdl/window.hpp"

constexpr auto IMG_FLAGS = IMG_INIT_PNG | IMG_INIT_JPG;

Context::Context(const WindowOptions& window_options) : window{window_options} {
	check_error((IMG_Init(IMG_FLAGS) & IMG_FLAGS) == IMG_FLAGS, IMG_GetError);
}

Context::~Context() {
	IMG_Quit();
}

auto Context::create_scene() -> Scene {
	return Scene{};
}
