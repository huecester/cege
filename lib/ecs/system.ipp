#pragma once

#include "entity.hpp"

template <typename T>
inline auto SystemManager::create_system() -> T& {
	auto type_name = typeid(T).name();

	if (systems.find(type_name) != systems.end())
		throw std::runtime_error{fmt::format("System `{}` cannot be created more than once.", type_name)};

	systems.insert({type_name, T{scene}});
	auto search = systems.find(type_name);
	return static_cast<T&>(search->second);
}

template <typename T>
inline auto SystemManager::set_signature(Signature signature) -> void {
	auto type_name = typeid(T).name();
	signatures.insert_or_assign(type_name, signature);
}
