#pragma once

#include <functional>

using EntityId = unsigned long long;

template <typename... Args>
using Handler = std::function<void(Args &&...)>;
