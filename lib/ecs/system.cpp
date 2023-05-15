#include "system.hpp"

#include <functional>

#include "entity.hpp"
#include "types.hpp"

auto entity_cmp(std::reference_wrapper<Entity> lhs, std::reference_wrapper<Entity> rhs) -> bool {
	return lhs.get().get_id() < rhs.get().get_id();
}

auto SystemManager::entity_destroyed(std::reference_wrapper<Entity> entity) -> void {
	for (auto &[_, system] : systems)
		system.entities.erase(entity);
}

auto SystemManager::entity_signature_changed(std::reference_wrapper<Entity> entity, Signature signature) -> void {
	for (auto &[type, system] : systems) {
		auto system_signature = signatures[type];

		if ((signature & system_signature) == system_signature)
			system.entities.insert(entity);
		else
			system.entities.erase(entity);
	}
}