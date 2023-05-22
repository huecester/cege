#include "system.hpp"

#include <algorithm>
#include <functional>
#include <memory>
#include <utility>

#include "entity.hpp"
#include "scene.hpp"
#include "types.hpp"

auto SystemManager::entity_destroyed(std::shared_ptr<Entity> entity) -> void {
	for (auto& [_, system] : systems)
		system.entities.erase(entity);
}

auto SystemManager::entity_signature_changed(std::shared_ptr<Entity> entity, Signature signature) -> void {
	for (auto& [type, system] : systems) {
		auto entity_ptr = std::shared_ptr{entity};
		auto system_signature = signatures[type];

		if ((signature & system_signature) == system_signature)
			system.entities.insert(entity_ptr);
		else
			system.entities.erase(entity_ptr);
	}
}
