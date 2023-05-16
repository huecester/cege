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

auto SystemManager::entity_destroyed(EntityId entity) -> void {
	for (auto& [_, system] : systems)
		system.ids.erase(entity);
}

auto SystemManager::entity_signature_changed(EntityId entity, Signature signature) -> void {
	for (auto& [type, system] : systems) {
		auto system_signature = signatures[type];

		if ((signature & system_signature) == system_signature)
			system.ids.insert(entity);
		else
			system.ids.erase(entity);
	}
}
