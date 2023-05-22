#include "entity.hpp"

#include <fmt/core.h>

#include <functional>
#include <ranges>
#include <stdexcept>

#include "constants.hpp"
#include "scene.hpp"

Entity::Entity(Scene *scene, EntityId id) : scene{scene}, id{id} {}

Entity::~Entity() {
	scene->destroy_entity(*this);
}

auto Entity::get_id() const -> EntityId { return id; }
auto Entity::get_signature() const -> Signature { return signature; }
auto Entity::set_signature(Signature signature) -> void { this->signature = signature; }

EntityManager::EntityManager() {
	for (auto i : std::ranges::views::iota(0, MAX_ENTITIES))
		available_ids.push(i);
}

auto EntityManager::create_entity(Scene *scene) -> std::shared_ptr<Entity> {
	if (available_ids.empty())
		throw std::length_error{"Too many entities."};

	auto id = available_ids.front();
	available_ids.pop();

	auto entity = std::make_shared<Entity>(scene, id);
	entities.at(id) = entity;
	return entity;
}

auto EntityManager::get_entity(EntityId id) -> std::shared_ptr<Entity> {
	auto entity_ptr = entities.at(id);
	if (entity_ptr.expired())
		throw std::runtime_error{fmt::format("No entity with ID `{}` exists.", id)};

	auto entity = entity_ptr.lock();
	if (entity == nullptr)
		throw std::runtime_error{fmt::format("No entity with ID `{}` exists.", id)};
	return entity;
}

auto EntityManager::destroy_entity(EntityId id) -> void {
	entities.at(id).reset();
}
