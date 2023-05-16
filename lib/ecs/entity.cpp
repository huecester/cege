#include "entity.hpp"

#include <fmt/core.h>

#include <ranges>
#include <stdexcept>

#include "constants.hpp"
#include "scene.hpp"

Entity::Entity(Scene &scene, EntityId id) : scene{scene}, id{id} {}

Entity::~Entity() {
	scene.destroy_entity(*this);
}

auto Entity::get_id() const -> EntityId { return id; }

EntityManager::EntityManager() {
	for (auto i : std::ranges::views::iota(0, MAX_ENTITIES))
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

auto Entity::get_signature() const -> Signature { return signature; }
auto Entity::set_signature(Signature signature) -> void { this->signature = signature; }
