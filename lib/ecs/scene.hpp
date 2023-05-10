#pragma once

#include <memory>

#include "types.hpp"

class ComponentManager;
class Entity;
class EntityManager;
class EventManager;

/// @brief A container that manages a single ECS.
class Scene {
   public:
	/// @brief Create an entity.
	/// @return The entity.
	/// @throw std::length_error Throws if too many entities are created.
	auto create_entity() -> Entity;

	/// @brief Destroy an entity.
	/// @param entity The entity to be destroyed.
	auto destroy_entity(Entity &&entity) -> void;

	/// @brief Destroy an entity.
	/// @param id The ID of the entity to be destroyed.
	auto destroy_entity(EntityId id) -> void;

	/// @brief Get an entity's component.
	/// @tparam T The component type to get.
	/// @param entity The entity to get the component of.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity doesn't have a component of this type.
	template <typename T>
	auto get_component(const Entity &entity) -> T &;

	/// @brief Get an entity's component.
	/// @tparam T The component type to get.
	/// @param id The entity ID to get the component of.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity doesn't have a component of this type.
	template <typename T>
	auto get_component(EntityId id) -> T &;

	/// @brief Create a component in place.
	/// @tparam T The component type to create.
	/// @tparam ...Args Argument types for the component constructor.
	/// @param entity The entity to assign this component to.
	/// @param ...args The arguments to forward to the component constructor.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	template <typename T, typename... Args>
	auto create_component(const Entity &entity, Args &&...args) -> T &;

	/// @brief Create a component in place.
	/// @tparam T The component type to create.
	/// @tparam ...Args Argument types for the component constructor.
	/// @param id The entity ID to assign this component to.
	/// @param ...args The arguments to forward to the component constructor.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	template <typename T, typename... Args>
	auto create_component(EntityId id, Args &&...args) -> T &;

	/// @brief Set an entity's component.
	/// @tparam T The component type to set.
	/// @param entity The entity to assign this component to.
	/// @param component The component to assign.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	template <typename T>
	auto set_component(const Entity &entity, T &&component) -> T &;

	/// @brief Set an entity's component.
	/// @tparam T The component type to set.
	/// @param id The entity ID to assign this component to.
	/// @param component The component to assign.
	/// @return A reference to the component.
	/// @throw std::runtime_error Throws if the entity already has a component of this type.
	template <typename T>
	auto set_component(EntityId id, T &&component) -> T &;

	/// @brief Remove an entity's component.
	/// @tparam T The component type to remove.
	/// @param entity The entity to remove the component from.
	/// @return The component.
	/// @throw std::runtime_error Throws if the entity doesn't have a component of this type.
	template <typename T>
	auto remove_component(const Entity &entity) -> T;

	/// @brief Remove an entity's component.
	/// @tparam T The component type to remove.
	/// @param id The entity ID to remove the component from.
	/// @return The component.
	/// @throw std::runtime_error Throws if the entity doesn't have a component of this type.
	template <typename T>
	auto remove_component(EntityId id) -> T;

	/// @brief Add a handler to a certain event/argument pair.
	/// @tparam ...Args Argument types for the event handlers.
	/// @param event_name The event to listen for.
	/// @param handler The handler to be called when the event is dispatched.
	template <typename... Args>
	auto add_event_handler(const char *event_name, Handler<Args...> handler) -> void;

	/// @brief Dispatch an event.
	/// @tparam ...Args Argument types for the event handlers.
	/// @param event_name The event to dispatch.
	/// @param ...args The arguments to pass to the event handlers.
	template <typename... Args>
	auto dispatch_event(const char *event_name, Args &&...args) const -> void;

   private:
	std::unique_ptr<ComponentManager> component_manager{};
	std::unique_ptr<EntityManager> entity_manager{};
	std::unique_ptr<EventManager> event_manager{};
};

#include "scene.ipp"
