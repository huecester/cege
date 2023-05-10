#include "context.hpp"

#include <SDL_image.h>
#include <doctest.h>

TEST_CASE("only one context is created") {
	auto &instance1 = Context::get_instance();
	auto &instance2 = Context::get_instance();

	CHECK(&instance1 == &instance2);
}

TEST_CASE("context initializes SDL_image") {
	Context::get_instance();

	CHECK(IMG_Init(0) > 0);
}
