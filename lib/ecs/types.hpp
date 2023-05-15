#pragma once

#include <bitset>
#include <functional>

#include "constants.hpp"

using EntityId = unsigned long long;
using ComponentId = unsigned char;
using Signature = std::bitset<MAX_COMPONENTS>;
