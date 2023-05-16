#pragma once

#include <bitset>
#include <functional>

#include "constants.hpp"

/// @brief A unique identifier for an entity.
using EntityId = unsigned long long;
/// @brief A unique identifier for a component type.
using ComponentId = unsigned char;
/// @brief A bitset used to identify which components an entity has.
using Signature = std::bitset<MAX_COMPONENTS>;
