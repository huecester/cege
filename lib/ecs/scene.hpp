#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <string_view>

#include "types.hpp"

class ComponentManager;
class Entity;
class EntityManager;
class SystemManager;

/// @brief A container that manages a single ECS.
class Scene {
   public:
	Scene();

	/// @brief Create an entity.
	/// @return The entity.
	/// @throw std::length_error Throws if too many entities are created.
	auto create_entity() -> Entity;

	/// @brief Create an entity from an ID.
	///
	/// This override is mainly used to create an entity from an ID that references an already existing entity without having to pass around references or pointers.
	///
	/// @return The entity.
	/// @throw std::length_error Throws if too many entities are created.
	auto create_entity(EntityId id) -> Entity;

	/// @brief Destroy an entity.
	/// @param entity The entity to be destroyed.
	auto destroy_entity(Entity &entity) -> void;

	/// @brief Get an entity's component.
	/// @tparam T The component type to get.
	/// @param entity The entity to get the component of.
	/// @return A reference to the component, or std::nullopt if the entity doesn't have this component.
	template <typename T>
	auto get_component(const Entity &entity) -> std::optional<std::reference_wrapper<T>>;

	/// @brief Create a component in place.
	/// @tparam T The component type to create.
	/// @tparam ...Args Argument types for the component constructor.
	/// @param entity The entity to assign this component to.
	/// @param ...args The arguments to forward to the component constructor.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	template <typename T, typename... Args>
	auto create_component(Entity &entity, Args &&...args) -> T &;

	/// @brief Set an entity's component.
	/// @tparam T The component type to set.
	/// @param entity The entity to assign this component to.
	/// @param component The component to assign.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	template <typename T>
	auto set_component(Entity &entity, T &&component) -> T &;

	/// @brief Remove an entity's component.
	/// @tparam T The component type to remove.
	/// @param entity The entity to remove the component from.
	/// @return The component, or std::nullopt if the entity doesn't have this component.
	template <typename T>
	auto remove_component(Entity &entity) -> std::optional<T>;

	/// @brief Create a system.
	/// @tparam T The system to create.
	/// @return A reference to the system instance.
	/// @throw std::runtime_error Throws if the system has already been created.
	template <typename T>
	auto create_system() -> T &;

	/// @brief Create a system.
	/// @tparam T The system to create.
	/// @tparam Sig1 A component type to use for the signature.
	/// @tparam ...Sigs The rest of the component types to use for the signature.
	/// @return A reference to the system instance.
	/// @throw std::runtime_error Throws if the system has already been created.
	template <typename T, typename Sig1, typename... Sigs>
	auto create_system() -> T &;

	/// @brief Create a signature from a component type.
	/// @tparam T The component type to create a signature of.
	/// @return The signature.
	template <typename T>
	auto create_signature() const -> Signature;

	/// @brief Create a signature from a list of component types.
	///
	/// @internal
	/// @tparam T1 The first component type.
	/// @tparam T2 The second component type.
	/// @tparam ...TN The rest of the component types.
	/// @endinternal
	///
	/// @return The signature
	template <typename T1, typename T2, typename... TN>
	auto create_signature() const -> Signature;

	/// @brief Set a system's signature.
	/// @tparam T The system to set the signature of.
	/// @param signature The signature to set.
	template <typename T>
	auto set_system_signature(Signature signature) -> void;

	/// @brief Set a system's signature.
	/// @tparam T The system to set the signature of.
	/// @tparam Sig1 A component type to use for the signature.
	/// @tparam ...Sigs The rest of the component types to use for the signature.
	template <typename T, typename Sig1, typename... Sigs>
	auto set_system_signature() -> void;

   private:
	std::unique_ptr<EntityManager> entity_manager;
	std::unique_ptr<ComponentManager> component_manager;
	std::unique_ptr<SystemManager> system_manager;
};

#include "scene.ipp"
