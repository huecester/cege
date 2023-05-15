#pragma once

#include <fmt/core.h>

#include <functional>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "types.hpp"

class Entity;

/// @brief Comparator for a set of `std::reference_wrapper<Entity>`'s.
auto entity_cmp(std::reference_wrapper<Entity> lhs, std::reference_wrapper<Entity> rhs) -> bool;

/// @brief A class to store references to entities that a system cares about.
///
/// Systems should inherit from this class and set their signature in the `SystemManager`.
/// Signatures determine the types of entities that will be stored in the `entities` variable.
/// Signatures store information on the components that an entity should have to be stored in this system.
class System {
   public:
	std::set<std::reference_wrapper<Entity>, decltype(&entity_cmp)> entities;

	virtual ~System() = default;
};

/// @brief A class to store and manage systems.
///
/// Systems that have inherited from `System` can be instantiated here using `create_system`.
class SystemManager {
   public:
	/// @brief Create a system.
	/// @tparam T The system to create.
	/// @return A reference to the system instance.
	/// @throw Throws if the system has already been created.
	template <typename T>
	auto create_system() -> T &;

	/// @brief Set a system's signature.
	/// @tparam T The system to set the signature of.
	/// @param signature The signature to set.
	template <typename T>
	auto set_signature(Signature signature) -> void;

	auto entity_destroyed(std::reference_wrapper<Entity> entity) -> void;
	auto entity_signature_changed(std::reference_wrapper<Entity> entity, Signature signature) -> void;

   private:
	std::unordered_map<std::string, Signature> signatures{};
	std::unordered_map<std::string, System> systems{};
};

#include "system.ipp"
