#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "context.hpp"

TEST_CASE("only one context is created") {
	auto &instance1 = Context::get_instance();
	auto &instance2 = Context::get_instance();

	CHECK(&instance1 == &instance2);
}
