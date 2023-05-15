#pragma once
#include <utility>

#include "scene.hpp"

template <typename T>
inline auto Entity::get_component() -> T & {
	return scene.get_component<T>(*this);
}

template <typename T, typename... Args>
inline auto Entity::create_component(Args &&...args) -> T & {
	return scene.create_component<T>(*this, std::forward<Args>(args)...);
}

template <typename T>
inline auto Entity::set_component(T &&component) -> T & {
	return scene.set_component<T>(*this, std::move(component));
}

template <typename T>
inline auto Entity::remove_component() -> T {
	return scene.remove_component<T>(*this);
}