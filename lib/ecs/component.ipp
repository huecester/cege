#pragma once

#include <fmt/core.h>

#include <utility>

#include "component.hpp"
#include "types.hpp"

template <typename T>
inline auto ComponentArray<T>::get_component(EntityId id) -> std::optional<std::reference_wrapper<T>> {
	auto index_search = id_to_index_map.find(id);
	if (index_search == id_to_index_map.end())
		return {};
	auto [_, index] = *index_search;
	return std::ref(components[index]);
}

template <typename T>
template <typename... Args>
inline auto ComponentArray<T>::create_component(EntityId id, Args&&... args) -> T& {
	return set_component(id, {std::forward<Args>(args)...});
}

template <typename T>
inline auto ComponentArray<T>::set_component(EntityId id, T&& component) -> T& {
	if (id_to_index_map.find(id) != id_to_index_map.end())
		throw std::runtime_error{fmt::format("Cannot add component `{}` to entity {} more than once.", typeid(T).name(), id)};

	auto new_index = len++;
	id_to_index_map[id] = new_index;
	index_to_id_map[new_index] = id;
	components[new_index] = component;

	return components[new_index];
}

template <typename T>
inline auto ComponentArray<T>::remove_component(EntityId target_id) -> std::optional<T> {
	if (id_to_index_map.find(target_id) == id_to_index_map.end())
		return {};

	auto target_index = id_to_index_map[target_id];
	auto last_index = --len;
	auto target_component = components[target_index];
	components[target_index] = components[last_index];

	auto last_id = index_to_id_map[last_index];
	id_to_index_map[last_id] = target_index;
	index_to_id_map[target_index] = last_id;

	id_to_index_map.erase(target_id);
	index_to_id_map.erase(last_index);

	return target_component;
}

template <typename T>
inline auto ComponentArray<T>::entity_destroyed(EntityId id) -> void {
	if (id_to_index_map.find(id) != id_to_index_map.end())
		remove_component(id);
}

template <typename T>
inline auto ComponentManager::get_component(EntityId id) -> std::optional<std::reference_wrapper<T>> {
	return get_component_array<T>().get_component(id);
}

template <typename T, typename... Args>
inline auto ComponentManager::create_component(EntityId id, Args&&... args) -> T& {
	return get_component_array<T>().create_component(id, std::forward<Args>(args)...);
}

template <typename T>
inline auto ComponentManager::set_component(EntityId id, T&& component) -> T& {
	return get_component_array<T>().set_component(id, std::move(component));
}

template <typename T>
inline auto ComponentManager::remove_component(EntityId id) -> std::optional<T> {
	return get_component_array<T>().remove_component(id);
}

template <typename T>
inline auto ComponentManager::get_component_id() -> ComponentId {
	auto type_name = typeid(T).name();

	auto search = component_ids.find(type_name);
	if (search == component_ids.end()) {
		register_component_array<T>();
		search = component_ids.find(type_name);
	}

	return search->second;
}

template <typename T>
inline auto ComponentManager::get_component_array() -> ComponentArray<T>& {
	auto type_name = typeid(T).name();
	auto search = component_arrays.find(type_name);
	if (search == component_arrays.end()) {
		register_component_array<T>();
		search = component_arrays.find(type_name);
	}
	return static_cast<ComponentArray<T>&>(*(search->second));
}

template <typename T>
inline auto ComponentManager::register_component_array() -> void {
	if (next_component_id >= MAX_COMPONENTS)
		throw std::length_error{"Too many components registered."};

	auto type_name = typeid(T).name();
	if (component_arrays.find(type_name) != component_arrays.end()) return;
	component_arrays.insert({type_name, std::make_unique<ComponentArray<T>>()});
	component_ids.insert({type_name, next_component_id++});
}