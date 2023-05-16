#pragma once

#include <optional>
#include <queue>

#include "types.hpp"

class Scene;

/// @brief Helper class to manage an entity.
class Entity {
   public:
	Entity(Scene *scene, EntityId id);

	/// @brief Get this entity's ID.
	/// @return This entity's ID.
	auto get_id() const -> EntityId;

	/// @brief Get a component.
	/// @tparam T The component type to get.
	/// @return A reference to the component, or std::nullopt if the entity doesn't have this component.
	template <typename T>
	auto get_component() -> std::optional<std::reference_wrapper<T>>;

	/// @brief Create a component in place.
	/// @tparam T The component type to create.
	/// @tparam ...Args Argument types for the component constructor.
	/// @param ...args The arguments to forward to the component constructor.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	template <typename T, typename... Args>
	auto create_component(Args &&...args) -> T &;

	/// @brief Set a component.
	/// @tparam T The component type to set.
	/// @param component The component to assign.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	template <typename T>
	auto set_component(T &&component) -> T &;

	/// @brief Remove a component.
	/// @tparam T The component type to remove.
	/// @return The component, or std::nullopt if the entity doesn't have this component.
	template <typename T>
	auto remove_component() -> std::optional<T>;

	/// @brief Destroy this entity.
	///
	/// Frees all resources associated to this entity, including IDs and any associated components.
	auto destroy() -> void;

	/// @internal
	/// @brief Get this entity's signature.
	///
	/// This signature represents all components that this entity owns.
	///
	/// @return The signature.
	auto get_signature() const -> Signature;

	/// @internal
	/// @brief Set this entity's signature.
	/// @param signature The signature to set.
	auto set_signature(Signature signature) -> void;

   private:
	Scene *scene;
	EntityId id;
	Signature signature;
};

/// @brief Manager for entity IDs.
class EntityManager {
   public:
	EntityManager();

	/// @brief Reserve an entity ID.
	/// @return An unused ID.
	/// @throw std::length_error Throws if too many entities are created.
	auto reserve_id() -> EntityId;

	/// @brief Free an entity ID to be used again.
	/// @param id The ID to be freed.
	/// @throw std::out_of_range Throws if an invalid entity ID is passed.
	auto free_id(EntityId id) -> void;

   private:
	std::queue<EntityId> available_ids{};
};

#include "entity.ipp"