#include "context.hpp"

#include "window.hpp"

auto Context::create_window(const char* title, int x, int y, int w, int h, Uint32 flags) -> Window {
	return Window{title, x, y, w, h, flags};
}

Context::Context() {}

auto Context::get_instance() -> Context& {
	static Context context{};
	return context;
}
