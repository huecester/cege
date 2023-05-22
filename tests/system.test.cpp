#include "ecs/system.hpp"

#include <doctest.h>

#include <algorithm>
#include <ranges>
#include <utility>
#include <vector>

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
			auto &foo = entity->get_component<Foo>()->get();
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
			auto &bar = entity->get_component<Bar>()->get();
			sum += bar.x;
		}

		return sum;
	}
};

TEST_CASE("systems work") {
	auto ctx = Context{TEST_WINDOW_OPTIONS};
	auto scene = ctx.create_scene();

	auto &foo_system = scene.create_system<FooSystem>();
	auto foo_signature = scene.create_signature<Foo>();
	scene.set_system_signature<FooSystem>(foo_signature);

	auto &bar_system = scene.create_system<BarSystem>();
	auto bar_signature = scene.create_signature<Bar>();
	scene.set_system_signature<BarSystem>(bar_signature);

	constexpr auto N_FOO_ENTITIES = 3;
	constexpr auto N_BAR_ENTITIES = 2;

	std::vector<std::shared_ptr<Entity>> foo_entities{};
	std::vector<std::shared_ptr<Entity>> bar_entities{};

	foo_entities.reserve(N_FOO_ENTITIES);
	bar_entities.reserve(N_BAR_ENTITIES);

	for ([[maybe_unused]] auto i : std::ranges::views::iota(0, N_FOO_ENTITIES)) {
		foo_entities.emplace_back(scene.create_entity());
	}

	for ([[maybe_unused]] auto i : std::ranges::views::iota(0, N_BAR_ENTITIES)) {
		bar_entities.emplace_back(scene.create_entity());
	}

	for (auto &entity : foo_entities) {
		entity->create_component<Foo>();
	}

	for (auto &entity : bar_entities) {
		entity->create_component<Bar>();
	}

	CHECK(foo_system.sum() == 3);
	CHECK(bar_system.sum() == 4);

	CHECK(foo_system.entities.size() == N_FOO_ENTITIES);
	CHECK(bar_system.entities.size() == N_BAR_ENTITIES);
}

struct Baz {
	int x = 3;
};

class TwoSystem : public System {
   public:
	auto product(Scene &scene) -> int {
		auto product = 1;
		for (auto &entity : entities) {
			product *= entity->get_component<Foo>()->get().x;
			product *= entity->get_component<Bar>()->get().x;
		}
		return product;
	}
};

class ThreeSystem : public System {
   public:
	auto product(Scene &scene) -> int {
		auto product = 1;
		for (auto &entity : entities) {
			product *= entity->get_component<Foo>()->get().x;
			product *= entity->get_component<Bar>()->get().x;
			product *= entity->get_component<Baz>()->get().x;
		}
		return product;
	}
};

TEST_CASE("systems can look for multiple components") {
	auto ctx = Context{TEST_WINDOW_OPTIONS};
	auto scene = ctx.create_scene();

	auto &two_system = scene.create_system<TwoSystem>();
	auto two_signature = scene.create_signature<Foo, Bar>();
	scene.set_system_signature<TwoSystem>(two_signature);

	auto &three_system = scene.create_system<ThreeSystem>();
	auto three_signature = scene.create_signature<Foo, Bar, Baz>();
	scene.set_system_signature<ThreeSystem>(three_signature);

	auto entity1 = scene.create_entity();
	entity1->create_component<Foo>();

	auto entity2 = scene.create_entity();
	entity2->create_component<Bar>();

	auto entity3 = scene.create_entity();
	entity3->create_component<Baz>();

	auto entity4 = scene.create_entity();
	entity4->create_component<Foo>();
	entity4->create_component<Bar>();

	auto entity5 = scene.create_entity();
	entity5->create_component<Foo>();
	entity5->create_component<Baz>();

	auto entity6 = scene.create_entity();
	entity6->create_component<Bar>();
	entity6->create_component<Baz>();

	auto entity7 = scene.create_entity();
	entity7->create_component<Foo>();
	entity7->create_component<Bar>();
	entity7->create_component<Baz>();

	CHECK(two_system.product(scene) == 4);
	CHECK(three_system.product(scene) == 6);

	CHECK(two_system.entities.size() == 2);
	CHECK(three_system.entities.size() == 1);
}
