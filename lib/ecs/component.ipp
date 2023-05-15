#pragma once

#include <fmt/core.h>

#include "component.hpp"
#include "types.hpp"

template <typename T>
inline auto ComponentArray<T>::get_component(EntityId id) -> T& {
	auto index_search = id_to_index_map.find(id);
	if (index_search == id_to_index_map.end())
		throw std::runtime_error{fmt::format("Entity {} does not have a(n) `{}` component.", id, typeid(T).name())};
	auto [_, index] = *index_search;
	return components[index];
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
inline auto ComponentArray<T>::remove_component(EntityId target_id) -> T {
	if (id_to_index_map.find(target_id) == id_to_index_map.end())
		throw std::runtime_error{fmt::format("Entity {} does not have a(n) `{}` component.", target_id, typeid(T).name())};

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
	auto type_name = typeid(T).name();
	if (component_arrays.find(type_name) != component_arrays.end())
		throw std::runtime_error{fmt::format("Component `{}` cannot be registered twice.", type_name)};
	component_arrays.insert({type_name, std::make_unique<ComponentArray<T>>()});
	component_ids.insert({type_name, next_component_id++});
}