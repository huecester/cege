#include "scene.hpp"

#include <functional>
#include <memory>

#include "component.hpp"
#include "entity.hpp"
#include "system.hpp"

Scene::Scene()
	: entity_manager{std::make_unique<EntityManager>()},
	  component_manager{std::make_unique<ComponentManager>()},
	  system_manager{std::make_unique<SystemManager>()} {}

auto Scene::create_entity() -> Entity {
	return Entity{*this, entity_manager->reserve_id()};
}

auto Scene::destroy_entity(Entity& entity) -> void {
	auto id = entity.get_id();

	entity_manager->free_id(id);
	component_manager->entity_destroyed(id);
	system_manager->entity_destroyed(std::ref(entity));
}
