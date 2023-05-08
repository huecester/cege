#pragma once

#include <memory>

#include "types.hpp"

class Entity;
class EntityManager;

/// @brief A container that manages a single ECS.
class Scene {
   public:
	/// @brief Create an entity.
	/// @return The entity.
	auto create_entity() -> Entity;

	/// @brief Destroy an entity.
	/// @param entity The entity to be destroyed.
	auto destroy_entity(Entity &&entity) -> void;

	auto destroy_entity(EntityID id) -> void;

   private:
	std::unique_ptr<EntityManager> entity_manager;
};