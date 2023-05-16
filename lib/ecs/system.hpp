#pragma once

#include <fmt/core.h>

#include <functional>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "types.hpp"

class Entity;
class Scene;

/// @brief A class to store references to entities that a system cares about.
///
/// Systems should inherit from this class and set their signature in the `SystemManager`.
/// Signatures determine the types of entities that will be stored in the `entities` variable.
/// Signatures store information on the components that an entity should have to be stored in this system.
class System {
   public:
	std::set<EntityId> ids;

	virtual ~System() = default;

   protected:
	auto get_entities(Scene &scene) const -> std::vector<Entity>;
};

/// @brief A class to store and manage systems.
///
/// Systems that have inherited from `System` can be instantiated here using `create_system`.
class SystemManager {
   public:
	/// @brief Create a system.
	/// @tparam T The system to create.
	/// @return A reference to the system instance.
	/// @throw std::runtime_error Throws if the system has already been created.
	template <typename T>
	auto create_system() -> T &;

	/// @brief Set a system's signature.
	/// @tparam T The system to set the signature of.
	/// @param signature The signature to set.
	template <typename T>
	auto set_signature(Signature signature) -> void;

	/// @internal
	/// @brief Remove an entity from all systems.
	///
	/// This method should be called by `Scene` when an entity is destroyed.
	///
	/// @param id The entity that was destroyed.
	auto entity_destroyed(EntityId id) -> void;

	/// @internal
	/// @brief Update all systems based on an entity's new signature.
	///
	/// This method should be called by `Scene` whenever an entity's signature changes.
	/// An entity's signature changes whenever its components update, such as when calling `create_component()` or `remove_component()`.
	///
	/// @param id The entity ID that changed.
	/// @param signature The new signature.
	auto entity_signature_changed(EntityId id, Signature signature) -> void;

   private:
	std::unordered_map<std::string, Signature> signatures{};
	std::unordered_map<std::string, System> systems{};
};

#include "system.ipp"
