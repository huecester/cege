#include "ecs/scene.hpp"

#include <doctest.h>

#include <utility>

#include "context.hpp"

struct TestVector {
	int x, y;
};

TEST_CASE("scenes work") {
	auto &ctx = Context::get_instance();
	auto scene = ctx.create_scene();

	SUBCASE("entities can be created") {
		auto entity = scene.create_entity();

		SUBCASE("components can be created") {
			auto &component = entity.create_component<TestVector>(2, 5);

			CHECK(component.x == 2);
			CHECK(component.y == 5);
		}

		SUBCASE("components can be set") {
			TestVector vector{2, 5};
			auto &component = entity.set_component(std::move(vector));

			CHECK(component.x == 2);
			CHECK(component.y == 5);
		}

		SUBCASE("components can be got") {
			entity.create_component<TestVector>(2, 5);
			auto &component = entity.get_component<TestVector>();

			CHECK(component.x == 2);
			CHECK(component.y == 5);
		}

		SUBCASE("components can be modified") {
			auto &component1 = entity.create_component<TestVector>(2, 5);
			component1.x++;

			CHECK(component1.x == 3);

			auto &component2 = entity.get_component<TestVector>();

			CHECK(component2.x == 3);
			component2.x++;

			CHECK(component2.x == 4);
			CHECK(component1.x == 4);
		}

		SUBCASE("components can be removed") {
			entity.create_component<TestVector>(2, 5);
			auto component = entity.remove_component<TestVector>();

			CHECK(component.x == 2);
			CHECK(component.y == 5);
		}
	}
}
