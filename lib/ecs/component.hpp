#pragma once

#include <fmt/core.h>

#include <array>
#include <stdexcept>
#include <unordered_map>
#include <utility>

#include "constants.hpp"
#include "types.hpp"

/// @brief An interface to allow for an array of component arrays.
class GenericComponentArray {
   public:
	virtual ~GenericComponentArray() = default;
};

/// @brief A helper class for a packed array of components.
/// @tparam T The component type.
template <typename T>
class ComponentArray : public GenericComponentArray {
   public:
	ComponentArray(Scene& scene);

	/// @brief Get an entity's component.
	/// @param id The entity ID to get the component of.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity doesn't have a component of this type.
	auto get_component(EntityId id) const -> T&;

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
	/// @param id The entity ID to remove the component from.
	/// @return The component.
	/// @throw std::runtime_error Throws if the entity doesn't have a component of this type.
	auto remove_component(EntityId target_id) -> T;

   private:
	Scene& scene;

	std::array<T, MAX_ENTITIES> components;
	std::unordered_map<EntityId, size_t> idToIndexMap{};
	std::unordered_map<size_t, EntityId> indexToIdMap{};

	size_t len = 0;
};

/// @brief Helper class to manage components and assign them to entities.
class ComponentManager {
   public:
	ComponentManager(Scene& scene) : scene{scene} {};

	/// @brief Get an entity's component.
	/// @tparam T The component type to get.
	/// @param id The entity ID to get the component of.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity doesn't have a component of this type.
	template <typename T>
	auto get_component(EntityId id) const -> T& {
		return get_component_array<T>().get_component(id);
	}

	/// @brief Create a component in place.
	/// @tparam T The component type to create.
	/// @tparam ...Args Argument types for the component constructor.
	/// @param id The entity ID to assign this component to.
	/// @param ...args The arguments to forward to the component constructor.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	template <typename T, typename... Args>
	auto create_component(EntityId id, Args&&... args) -> T& {
		return get_component_array<T>().create_component(id, std::forward<Args>(args)...);
	}

	/// @brief Set an entity's component.
	/// @tparam T The component type to set.
	/// @param id The entity ID to assign this component to.
	/// @param component The component to assign.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	template <typename T>
	auto set_component(EntityId id, T&& component) -> T& {
		return get_component_array<T>().set_component(id, component);
	}

	/// @brief Remove an entity's component.
	/// @tparam T The component type to remove.
	/// @param id The entity ID to remove the component from.
	/// @return The component.
	/// @throw std::runtime_error Throws if the entity doesn't have a component of this type.
	template <typename T>
	auto remove_component(EntityId id) -> T {
		return get_component_array<T>().remove_component(id);
	}

   private:
	Scene& scene;

	std::unordered_map<const char*, std::unique_ptr<GenericComponentArray>> component_arrays{};

	/// @brief Get a component array.
	/// @tparam T The type of component array to get.
	/// @return A reference to the component array.
	template <typename T>
	auto get_component_array() -> ComponentArray<T>& {
		auto type_name = typeid(T).name();
		auto component_array = component_arrays.find(type_name);
		if (component_array == component_arrays.end()) {
			component_array = component_arrays.emplace({type_name, std::make_unique<ComponentArray<T>>(scene)});
		}
		return *component_array;
	}
};

#include "component.ipp"