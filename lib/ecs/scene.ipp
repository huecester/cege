#pragma once

#include <utility>

#include "component.hpp"
#include "entity.hpp"
#include "event.hpp"

template <typename T>
inline auto Scene::get_component(const Entity &entity) const -> T & {
	return component_manager->get_component<T>(entity.get_id());
}

template <typename T, typename... Args>
inline auto Scene::create_component(const Entity &entity, Args &&...args) -> T & {
	return component_manager->create_component<T>(entity.get_id(), std::forward<Args>(args)...);
}

template <typename T>
inline auto Scene::set_component(const Entity &entity, T &&component) -> T & {
	return component_manager->set_component(entity.get_id(), component);
}

template <typename T>
inline auto Scene::remove_component(const Entity &entity) -> T {
	return component_manager->remove_component<T>(entity.get_id());
}

template <typename... Args>
inline auto Scene::add_event_handler(const char *event_name, typename Event<Args...>::Handler &&handler) -> void {
	event_manager->add_handler(event_name, handler);
}

template <typename... Args>
inline auto Scene::dispatch_event(const char *event_name, Args &&...args) const -> void {
	event_manager->dispatch(event_name, std::forward<Args>(args)...);
}