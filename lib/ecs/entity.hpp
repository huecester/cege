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
	auto reserve_id() -> EntityID;

	/// @brief Free an entity ID to be used again.
	/// @param id The ID to be freed.
	auto free_id(EntityID id) -> void;

   private:
	Scene &scene;
	std::queue<EntityID> available_ids;
};

/// @brief Helper class to manage an entity.
class Entity {
   public:
	Entity(Scene &scene, EntityID id) : scene{scene}, id{id} {};
	~Entity();

	auto get_id() -> EntityID { return id; }

   private:
	Scene &scene;
	EntityID id;
};