#include <SDL.h>

#include "context.hpp"
#include "ecs/scene.hpp"
#include "sdl/texture.hpp"
#include "sdl/window.hpp"

constexpr auto WINDOW_TITLE = "Hello, SDL!";
constexpr auto WINDOW_WIDTH = 640;
constexpr auto WINDOW_HEIGHT = 480;

constexpr auto WINDOW_FLAGS = SDL_WINDOW_SHOWN;
constexpr auto RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

constexpr WindowOptions WINDOW_OPTIONS{WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS, RENDERER_FLAGS};

constexpr auto FIXED_TIMESTEP_MS = 1000 / 60;  // 60fps -> 1000 ms per 60 frames

struct Vector2 {
	float x, y;
};

struct Transform {
	Vector2 position;
	Vector2 scale{1.0f, 1.0f};
	float rotation;
};

struct Player {
	float speed = 200.0f;
	float scale_rate = 0.5f;
	float angular_velocity = 90.0f;
};

class RenderSystem : public System {
   public:
	auto render(Scene &scene, Window &window) -> void {
		window.set_clear_color(0xaa, 0xaa, 0xaa);
		window.clear();

		for (auto &entity : get_entities(scene)) {
			auto &texture = entity.get_component<Texture>()->get();
			auto &transform = entity.get_component<Transform>()->get();

			SDL_Rect dstrect{
				.x = static_cast<int>(transform.position.x),
				.y = static_cast<int>(transform.position.y),
				.w = static_cast<int>(texture.get_width() * transform.scale.x),
				.h = static_cast<int>(texture.get_height() * transform.scale.y),
			};

			window.render(texture, nullptr, &dstrect, transform.rotation, nullptr);
		}

		window.present();
	}
};

class PlayerSystem : public System {
   public:
	auto move(Scene &scene, float delta) -> void {
		for (auto &entity : get_entities(scene)) {
			auto &transform = entity.get_component<Transform>()->get();
			auto &player = entity.get_component<Player>()->get();

			const auto keyboard_states = SDL_GetKeyboardState(nullptr);

			if (keyboard_states[SDL_SCANCODE_W])
				transform.position.y -= player.speed * delta;
			if (keyboard_states[SDL_SCANCODE_A])
				transform.position.x -= player.speed * delta;
			if (keyboard_states[SDL_SCANCODE_S])
				transform.position.y += player.speed * delta;
			if (keyboard_states[SDL_SCANCODE_D])
				transform.position.x += player.speed * delta;

			if (keyboard_states[SDL_SCANCODE_UP]) {
				transform.scale.x += player.scale_rate * delta;
				transform.scale.y += player.scale_rate * delta;
			}
			if (keyboard_states[SDL_SCANCODE_DOWN]) {
				transform.scale.x -= player.scale_rate * delta;
				transform.scale.y -= player.scale_rate * delta;
			}

			if (keyboard_states[SDL_SCANCODE_Q])
				transform.rotation -= player.angular_velocity * delta;
			if (keyboard_states[SDL_SCANCODE_E])
				transform.rotation += player.angular_velocity * delta;
		}
	}
};

int main() {
	Context ctx{WINDOW_OPTIONS};
	auto &window = ctx.get_window();
	auto scene = ctx.create_scene();

	// Systems
	auto &render_system = scene.create_system<RenderSystem, Transform, Texture>();
	auto &player_system = scene.create_system<PlayerSystem, Transform, Player>();

	// Entities
	auto rick = scene.create_entity();
	rick.create_component<Transform>();
	rick.create_component<Texture>("assets/rick_astley.png", window.get_renderer());
	rick.create_component<Player>();

	SDL_Event e;
	bool quit = false;

	auto prev = SDL_GetTicks64();
	auto prev_fixed = prev;

	while (quit == false) {
		// Events
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) quit = true;
		}

		auto now = SDL_GetTicks64();

		// Fixed loop
		auto delta_fixed = now - prev_fixed;
		if (delta_fixed >= FIXED_TIMESTEP_MS) {
			// Fixed update
			// auto delta_fixed_s = delta_fixed / 1000.0f;
			// fixed_update_system.update(delta_fixed_s);
			prev_fixed += FIXED_TIMESTEP_MS;
		}

		// Variable loop/update
		auto delta = now - prev;
		prev = now;
		auto delta_s = delta / 1000.0f;
		// update_system.update(delta_s);
		player_system.move(scene, delta_s);

		// Render
		render_system.render(scene, window);
	}
}