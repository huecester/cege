#include "system.hpp"

#include <algorithm>
#include <functional>

#include "entity.hpp"
#include "scene.hpp"
#include "types.hpp"

auto System::get_entities(Scene& scene) const -> std::vector<Entity> {
	std::vector<Entity> entities{};

	for (auto id : ids)
		entities.push_back(scene.create_entity(id));

	return entities;
}

auto SystemManager::entity_destroyed(EntityId id) -> void {
	for (auto& [_, system] : systems)
		system.ids.erase(id);
}

auto SystemManager::entity_signature_changed(EntityId id, Signature signature) -> void {
	for (auto& [type, system] : systems) {
		auto system_signature = signatures[type];

		if ((signature & system_signature) == system_signature)
			system.ids.insert(id);
		else
			system.ids.erase(id);
	}
}
