#pragma once

#include <array>
#include <functional>
#include <optional>
#include <string>
#include <unordered_map>

#include "constants.hpp"
#include "types.hpp"

/// @brief An interface to allow storing a collection of component arrays.
class GenericComponentArray {
   public:
	virtual ~GenericComponentArray() = default;
	virtual auto entity_destroyed(EntityId id) -> void = 0;
};

/// @brief A helper class for a packed array of components.
/// @tparam T The component type.
template <typename T>
class ComponentArray : public GenericComponentArray {
   public:
	/// @brief Get an entity's component.
	/// @param id The entity ID to get the component of.
	/// @return A reference to the component, or std::nullopt if the entity doesn't have this component.
	auto get_component(EntityId id) -> std::optional<std::reference_wrapper<T>>;

	/// @brief Create a component in place.
	/// @tparam ...Args Argument types for the component constructor.
	/// @param id The entity ID to assign this component to.
	/// @param ...args The arguments to forward to the component constructor.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	template <typename... Args>
	auto create_component(EntityId id, Args&&... args) -> T&;

	/// @brief Set an entity's component.
	/// @param id The entity ID to assign this component to.
	/// @param component The component to assign.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	auto set_component(EntityId id, T&& component) -> T&;

	/// @brief Remove an entity's component.
	/// @param target_id The entity ID to remove the component from.
	/// @return The component, or std::nullopt if the entity doesn't have this component.
	auto remove_component(EntityId target_id) -> std::optional<T>;

	/// @internal
	/// @brief Remove an entity's component.
	///
	/// This method should be called by `ComponentManager` when an entity is destroyed.
	///
	/// @param id The entity ID that was destroyed.
	auto entity_destroyed(EntityId id) -> void override;

   private:
	std::array<T, MAX_ENTITIES> components{};
	std::unordered_map<EntityId, size_t> id_to_index_map{};
	std::unordered_map<size_t, EntityId> index_to_id_map{};

	size_t len = 0;
};

/// @brief Helper class to manage components and assign them to entities.
class ComponentManager {
   public:
	/// @brief Get an entity's component.
	/// @tparam T The component type to get.
	/// @param id The entity ID to get the component of.
	/// @return A reference to the component, or std::nullopt if the entity doesn't have this component.
	template <typename T>
	auto get_component(EntityId id) -> std::optional<std::reference_wrapper<T>>;

	/// @brief Create a component in place.
	/// @tparam T The component type to create.
	/// @tparam ...Args Argument types for the component constructor.
	/// @param id The entity ID to assign this component to.
	/// @param ...args The arguments to forward to the component constructor.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	template <typename T, typename... Args>
	auto create_component(EntityId id, Args&&... args) -> T&;

	/// @brief Set an entity's component.
	/// @tparam T The component type to set.
	/// @param id The entity ID to assign this component to.
	/// @param component The component to assign.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	template <typename T>
	auto set_component(EntityId id, T&& component) -> T&;

	/// @brief Remove an entity's component.
	/// @tparam T The component type to remove.
	/// @param id The entity ID to remove the component from.
	/// @return The component, or std::nullopt if the entity doesn't have this component.
	template <typename T>
	auto remove_component(EntityId id) -> std::optional<T>;

	/// @brief Get a component's ID.
	/// @tparam T The component type to get the ID of.
	/// @return The component's ID.
	template <typename T>
	auto get_component_id() -> ComponentId;

	/// @internal
	/// @brief Remove all of an entity's components.
	///
	/// This method should be called by `Scene` when an entity is destroyed.
	///
	/// @param id The entity ID that was destroyed.
	auto entity_destroyed(EntityId id) -> void;

   private:
	std::unordered_map<std::string, std::unique_ptr<GenericComponentArray>> component_arrays{};
	std::unordered_map<std::string, ComponentId> component_ids{};
	ComponentId next_component_id = 0;

	/// @internal
	/// @brief Get a component array.
	/// @tparam T The component type to get the array of.
	/// @return A reference to the component array.
	template <typename T>
	auto get_component_array() -> ComponentArray<T>&;

	/// @brief Register a new component array.
	/// @tparam T The component type to register.
	/// @throw std::length_error Throws if too many components have already been registered.
	template <typename T>
	auto register_component_array() -> void;
};

#include "component.ipp"