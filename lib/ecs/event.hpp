#pragma once

#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include "types.hpp"

/// @brief An interface for a generic event.
class GenericEvent {
   public:
	virtual ~GenericEvent() = default;
};

/// @brief A helper class for managing the handlers of a certain event/argument pair.
/// @tparam ...Args Argument types for the event handlers.
template <typename... Args>
class Event : public GenericEvent {
   public:
	Event(std::string_view event_name) : event_name{event_name} {};

	/// @brief Add a handler to this event/argument pair.
	/// @param handler The handler to add.
	auto add_handler(Handler<Args...> handler) -> void;

	/// @brief Call all attached event handlers with arguments.
	/// @param ...args The arguments to pass to the event handlers.
	auto dispatch(Args &&...args) const -> void;

   private:
	std::string_view event_name;
	std::vector<Handler<Args...>> handlers{};
};

/// @brief A helper class for managing events and handlers.
class EventManager {
   public:
	/// @brief Add a handler to a certain event/argument pair.
	/// @tparam ...Args Argument types for the event handlers.
	/// @param event_name The event to listen for.
	/// @param handler The handler to be called when the event is dispatched.
	template <typename... Args>
	auto add_handler(std::string_view event_name, Handler<Args...> handler) -> void;

	/// @brief Dispatch an event.
	/// @tparam ...Args Argument types for the event handlers.
	/// @param event_name The event to dispatch.
	/// @param ...args The arguments to pass to the event handlers.
	template <typename... Args>
	auto dispatch(std::string_view event_name, Args &&...args) const -> void;

   private:
	std::unordered_map<std::string, GenericEvent> events{};
};

#include "event.ipp"
