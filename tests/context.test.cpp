#include "context.hpp"

#include <SDL_image.h>
#include <doctest.h>

#include "test_types.hpp"

TEST_CASE("context works") {
	auto ctx = Context{TEST_WINDOW_OPTIONS};

	REQUIRE(IMG_Init(0) > 0);

	SUBCASE("context initializes window") {
		auto &window = ctx.get_window();
	}
}
