#include "scene.hpp"

#include "entity.hpp"

auto Scene::create_entity() -> Entity {
	auto id = entity_manager->reserve_id();
	return Entity{*this, id};
}

auto Scene::destroy_entity(Entity&& entity) -> void {
	destroy_entity(entity.get_id());
}

auto Scene::destroy_entity(EntityId id) -> void {
	entity_manager->free_id(id);
}