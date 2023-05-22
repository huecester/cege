#include <doctest.h>

#include <utility>

#include "context.hpp"
#include "ecs/scene.hpp"
#include "test_types.hpp"

struct TestVector {
	int x, y;
};

TEST_CASE("components work") {
	auto ctx = Context{TEST_WINDOW_OPTIONS};
	auto scene = ctx.create_scene();
	auto entity = scene.create_entity();

	SUBCASE("components can be created") {
		auto &component = entity->create_component<TestVector>(2, 5);

		CHECK(component.x == 2);
		CHECK(component.y == 5);

		SUBCASE("components can be got") {
			auto &get_component = entity->get_component<TestVector>()->get();

			CHECK(get_component.x == 2);
			CHECK(get_component.y == 5);
		}

		SUBCASE("components can be modified") {
			component.x++;

			CHECK(component.x == 3);

			auto &get_component = entity->get_component<TestVector>()->get();

			CHECK(get_component.x == 3);
			get_component.x++;

			CHECK(get_component.x == 4);
			CHECK(component.x == 4);
		}
	}

	SUBCASE("components can be set") {
		TestVector vector{2, 5};
		auto &component = entity->set_component(std::move(vector));

		CHECK(component.x == 2);
		CHECK(component.y == 5);
	}

	SUBCASE("components can be removed") {
		entity->create_component<TestVector>(2, 5);
		auto component = *entity->remove_component<TestVector>();

		CHECK(component.x == 2);
		CHECK(component.y == 5);
	}
}
