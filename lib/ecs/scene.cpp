#include "scene.hpp"

#include <memory>
#include <vector>

#include "component.hpp"
#include "entity.hpp"
#include "system.hpp"

Scene::Scene()
	: entity_manager{std::make_unique<EntityManager>()},
	  component_manager{std::make_unique<ComponentManager>()},
	  system_manager{std::make_unique<SystemManager>()} {}

auto Scene::create_entity() -> std::shared_ptr<Entity> {
	return entity_manager->create_entity(this);
}

auto Scene::destroy_entity(Entity& entity) -> void {
	auto id = entity.get_id();
	auto entity_ptr = entity_manager->get_entity(id);

	entity_manager->destroy_entity(id);
	component_manager->entity_destroyed(id);
	system_manager->entity_destroyed(entity_ptr);
}
