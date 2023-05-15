#include "entity.hpp"

#include <fmt/core.h>

#include <ranges>
#include <stdexcept>

#include "constants.hpp"
#include "scene.hpp"

EntityManager::EntityManager() {
	for (auto i = 0; i < MAX_ENTITIES; i++)
		available_ids.push(i);
}

auto EntityManager::reserve_id() -> EntityId {
	if (available_ids.empty())
		throw std::length_error{"Too many entities."};

	auto id = available_ids.front();
	available_ids.pop();
	return id;
}

auto EntityManager::free_id(EntityId id) -> void {
	if (id >= MAX_ENTITIES)
		throw std::out_of_range{fmt::format("Entity ID {} is out of range.", id)};
	available_ids.push(id);
}

Entity::~Entity() {
	scene.destroy_entity(*this);
}
