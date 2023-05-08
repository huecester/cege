#include "context.hpp"

#include "window.hpp"

auto Context::create_window(const char* title, int x, int y, int w, int h, Uint32 windowFlags, Uint32 rendererFlags) -> Window {
	return Window{title, x, y, w, h, windowFlags, rendererFlags};
}

Context::Context() {}

auto Context::get_instance() -> Context& {
	static Context context{};
	return context;
}
