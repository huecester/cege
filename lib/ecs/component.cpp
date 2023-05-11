#include "component.hpp"

auto ComponentManager::entity_destroyed(EntityId id) -> void {
	for (auto &[_, component_array] : component_arrays)
		component_array->entity_destroyed(id);
}