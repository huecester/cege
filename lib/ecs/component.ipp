#pragma once

#include <utility>

#include "scene.hpp"
#include "types.hpp"

template <typename T>
inline ComponentArray<T>::ComponentArray(Scene& scene) : scene{scene} {
	Handler<EntityId> handler = [this](EntityId id) mutable {
		if (idToIndexMap.find(id) != idToIndexMap.end())
			remove_component(id);
	};

	scene.add_event_handler<EntityId>("EntityDestroyed", handler);
}

template <typename T>
inline auto ComponentArray<T>::get_component(EntityId id) -> T& {
	auto index_search = idToIndexMap.find(id);
	if (index_search == idToIndexMap.end())
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
	if (idToIndexMap.find(id) != idToIndexMap.end())
		throw std::runtime_error{fmt::format("Cannot add component `{}` to entity {} more than once.", typeid(T).name(), id)};

	auto new_index = len++;
	idToIndexMap[id] = new_index;
	indexToIdMap[new_index] = id;
	components[new_index] = component;

	return components[new_index];
}

template <typename T>
inline auto ComponentArray<T>::remove_component(EntityId target_id) -> T {
	if (idToIndexMap.find(target_id) == idToIndexMap.end())
		throw std::runtime_error{fmt::format("Entity {} does not have a(n) `{}` component.", target_id, typeid(T).name())};

	auto target_index = idToIndexMap[target_id];
	auto last_index = --len;
	auto target_component = components[target_index];
	components[target_index] = components[last_index];

	auto last_id = indexToIdMap[last_index];
	idToIndexMap[last_id] = target_index;
	indexToIdMap[target_index] = last_id;

	idToIndexMap.erase(target_id);
	indexToIdMap.erase(last_index);

	return target_component;
}
