#pragma once

#include "component.hpp"
#include "entity.hpp"

template <typename T>
inline auto Scene::get_component(const Entity &entity) -> T & {
	return get_component<T>(entity.get_id());
}

template <typename T>
inline auto Scene::get_component(EntityId id) -> T & {
	return component_manager->get_component<T>(id);
}

template <typename T, typename... Args>
inline auto Scene::create_component(const Entity &entity, Args &&...args) -> T & {
	return create_component<T>(entity.get_id(), std::forward<Args>(args)...);
}

template <typename T, typename... Args>
inline auto Scene::create_component(EntityId id, Args &&...args) -> T & {
	return component_manager->create_component<T>(id, std::forward<Args>(args)...);
}

template <typename T>
inline auto Scene::set_component(const Entity &entity, T &&component) -> T & {
	return set_component<T>(entity.get_id(), component);
}

template <typename T>
inline auto Scene::set_component(EntityId id, T &&component) -> T & {
	return component_manager->set_component<T>(id, std::move(component));
}

template <typename T>
inline auto Scene::remove_component(const Entity &entity) -> T {
	return remove_component<T>(entity.get_id());
}

template <typename T>
inline auto Scene::remove_component(EntityId id) -> T {
	return component_manager->remove_component<T>(id);
}
