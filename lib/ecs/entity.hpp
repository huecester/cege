#pragma once

#include <queue>

#include "types.hpp"

class Scene;

/// @brief Manager for entity IDs.
class EntityManager {
   public:
	EntityManager(Scene &scene);

	/// @brief Reserve an entity ID.
	/// @return An unused ID.
	/// @throw std::length_error Throws if too many entities are created.
	auto reserve_id() -> EntityId;

	/// @brief Free an entity ID to be used again.
	/// @param id The ID to be freed.
	/// @throw std::out_of_range Throws if an invalid entity ID is passed.
	auto free_id(EntityId id) -> void;

   private:
	Scene &scene;
	std::queue<EntityId> available_ids;
};

/// @brief Helper class to manage an entity.
class Entity {
   public:
	Entity(Scene &scene, EntityId id) : scene{scene}, id{id} {};
	~Entity();

	/// @brief Get this entity's ID.
	/// @return This entity's ID.
	auto get_id() const -> EntityId { return id; }

   private:
	Scene &scene;
	EntityId id;
};