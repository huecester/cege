#pragma once

template <typename... Args>
inline auto Event<Args...>::add_handler(Handler<Args...> handler) -> void {
	handlers.push_back(handler);
}

template <typename... Args>
inline auto Event<Args...>::dispatch(Args &&...args) const -> void {
	for (const auto handler : handlers) {
		handler(std::forward<Args>(args)...);
	}
}

template <typename... Args>
inline auto EventManager::add_handler(std::string_view event_name, Handler<Args...> handler) -> void {
	auto key = fmt::format("{}{}", event_name, typeid(Args).name()...);
	auto search = events.find(key);
	if (search == events.end()) {
		events.insert({key, Event<Args...>{event_name}});
		search = events.find(key);
	}

	auto [_, event] = *search;
	static_cast<Event<Args...> &>(event).add_handler(handler);
}

template <typename... Args>
inline auto EventManager::dispatch(std::string_view event_name, Args &&...args) const -> void {
	auto key = fmt::format("{}{}", event_name, typeid(Args).name()...);
	auto search = events.find(key);
	if (search == events.end()) return;

	auto [_, event] = *search;
	static_cast<Event<Args...> &>(event).dispatch(std::forward<Args>(args)...);
}
