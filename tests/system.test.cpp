#include "ecs/system.hpp"

#include <doctest.h>

#include <ranges>
#include <utility>

#include "context.hpp"
#include "ecs/scene.hpp"
#include "test_types.hpp"

struct Foo {
	int x = 1;
};

struct Bar {
	int x = 2;
};

class FooSystem : public System {
   public:
	auto sum() -> int {
		auto sum = 0;

		for (auto entity : entities) {
			auto &foo = entity.get().get_component<Foo>()->get();
			sum += foo.x;
		}

		return sum;
	}
};

class BarSystem : public System {
   public:
	auto sum() -> int {
		auto sum = 0;

		for (auto entity : entities) {
			auto &bar = entity.get().get_component<Bar>()->get();
			sum += bar.x;
		}

		return sum;
	}
};

TEST_CASE("systems work") {
	auto ctx = Context{TEST_WINDOW_OPTIONS};
	auto scene = ctx.create_scene();

	auto foo_system = scene.create_system<FooSystem>();
	auto foo_signature = scene.create_signature<Foo>();
	scene.set_system_signature<FooSystem>(foo_signature);

	auto bar_system = scene.create_system<BarSystem>();
	auto bar_signature = scene.create_signature<Bar>();
	scene.set_system_signature<BarSystem>(bar_signature);

	constexpr auto N_FOO_ENTITIES = 3;
	constexpr auto N_BAR_ENTITIES = 2;

	std::vector<Entity> foo_entities{};
	std::vector<Entity> bar_entities{};

	for ([[maybe_unused]] auto i : std::ranges::views::iota(0, N_FOO_ENTITIES)) {
		auto entity = scene.create_entity();
		entity.create_component<Foo>();
		foo_entities.push_back(std::move(entity));
	}

	for ([[maybe_unused]] auto i : std::ranges::views::iota(0, N_BAR_ENTITIES)) {
		auto entity = scene.create_entity();
		entity.create_component<Bar>();
		bar_entities.push_back(std::move(entity));
	}

	CHECK(foo_system.sum() == 3);
	CHECK(bar_system.sum() == 6);

	CHECK(foo_system.entities.size() == N_FOO_ENTITIES);
	CHECK(bar_system.entities.size() == N_BAR_ENTITIES);
}
