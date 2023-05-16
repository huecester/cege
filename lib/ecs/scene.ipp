#pragma once

#include <functional>

#include "component.hpp"
#include "entity.hpp"
#include "system.hpp"
#include "types.hpp"

template <typename T>
inline auto Scene::get_component(const Entity &entity) -> std::optional<std::reference_wrapper<T>> {
	return component_manager->get_component<T>(entity.get_id());
}

template <typename T, typename... Args>
inline auto Scene::create_component(Entity &entity, Args &&...args) -> T & {
	auto &component_ref = component_manager->create_component<T>(entity.get_id(), std::forward<Args>(args)...);

	auto signature = entity.get_signature();
	signature.set(component_manager->get_component_id<T>());
	entity.set_signature(signature);

	system_manager->entity_signature_changed(entity.get_id(), signature);

	return component_ref;
}

template <typename T>
inline auto Scene::set_component(Entity &entity, T &&component) -> T & {
	auto &component_ref = component_manager->set_component<T>(entity.get_id(), std::move(component));

	auto signature = entity.get_signature();
	signature.set(component_manager->get_component_id<T>());
	entity.set_signature(signature);

	system_manager->entity_signature_changed(entity.get_id(), signature);

	return component_ref;
}

template <typename T>
inline auto Scene::remove_component(Entity &entity) -> std::optional<T> {
	auto component = component_manager->remove_component<T>(entity.get_id());

	auto signature = entity.get_signature();
	signature.reset(component_manager->get_component_id<T>());
	entity.set_signature(signature);

	system_manager->entity_signature_changed(entity.get_id(), signature);

	return component;
}

template <typename T>
inline auto Scene::create_system() -> T & {
	return system_manager->create_system<T>();
}

template <typename T>
inline auto Scene::create_signature() const -> Signature {
	Signature signature{};
	auto component_id = component_manager->get_component_id<T>();
	signature.set(component_id);
	return signature;
}

template <typename T1, typename T2, typename... TN>
inline auto Scene::create_signature() const -> Signature {
	return create_signature<T1>() | create_signature<T2, TN...>();
}

template <typename T>
inline auto Scene::set_system_signature(Signature signature) -> void {
	system_manager->set_signature<T>(signature);
}