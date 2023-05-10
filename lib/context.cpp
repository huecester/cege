#include "context.hpp"

#include <SDL_image.h>

#include "ecs/scene.hpp"
#include "sdl/util.hpp"
#include "sdl/window.hpp"

constexpr auto IMG_FLAGS = IMG_INIT_PNG | IMG_INIT_JPG;

auto Context::create_window(const char* title, int x, int y, int w, int h, Uint32 windowFlags, Uint32 rendererFlags) -> Window {
	return Window{title, x, y, w, h, windowFlags, rendererFlags};
}

auto Context::create_scene() -> Scene {
	return Scene{};
}

auto Context::get_instance() -> Context& {
	static Context context{};
	return context;
}

Context::Context() {
	check_error(static_cast<bool>(!((IMG_Init(IMG_FLAGS) & IMG_FLAGS) ^ IMG_FLAGS)), IMG_GetError);
}

Context::~Context() {
	IMG_Quit();
}
