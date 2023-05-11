#include "scene.hpp"

#include "component.hpp"
#include "entity.hpp"
#include "event.hpp"

Scene::Scene()
	: event_manager{std::make_unique<EventManager>()},
	  entity_manager{std::make_unique<EntityManager>()},
	  component_manager{std::make_unique<ComponentManager>(*this)} {}

auto Scene::create_entity() -> Entity {
	return Entity{*this, entity_manager->reserve_id()};
}

auto Scene::destroy_entity(Entity&& entity) -> void {
	destroy_entity(entity.get_id());
}

auto Scene::destroy_entity(EntityId id) -> void {
	entity_manager->free_id(id);
	dispatch_event("EntityDestroyed", id);
}