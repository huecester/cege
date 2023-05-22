#include <SDL.h>

#include <cege.hpp>
#include <cmath>

constexpr auto WINDOW_TITLE = "Hello, SDL!";
constexpr auto WINDOW_WIDTH = 640;
constexpr auto WINDOW_HEIGHT = 480;

constexpr WindowOptions WINDOW_OPTIONS{WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT};

constexpr auto FIXED_TIMESTEP_MS = 1000 / 60;  // 60fps -> 1000 ms per 60 frames

struct Vector2 {
	float x, y;

	auto operator+(const Vector2 &other) const -> Vector2 {
		return Vector2{
			x + other.x,
			y + other.y,
		};
	}

	auto operator-(const Vector2 &other) const -> Vector2 {
		return Vector2{
			x - other.x,
			y - other.y,
		};
	}

	auto operator*(float scalar) const -> Vector2 {
		return Vector2{
			x * scalar,
			y * scalar,
		};
	}

	auto operator+=(const Vector2 &other) -> Vector2 & {
		x += other.x;
		y += other.y;
		return *this;
	}

	auto operator-=(const Vector2 &other) -> Vector2 & {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	auto operator*=(float scalar) -> Vector2 & {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	auto normalize() -> Vector2 & {
		auto length = std::sqrt(x * x + y * y);
		x /= length;
		y /= length;
		return *this;
	}
};

struct Transform {
	Vector2 position{0.0f, 0.0f};
	Vector2 scale{100.0f, 100.0f};
};

struct Player {
	float speed = 200.0f;
	float scale_rate = 0.5f;
	float angular_velocity = 90.0f;
};

struct Collider {
	bool stationary = false;
};

class RenderSystem : public System {
   public:
	auto render(Window &window) -> void {
		window.set_clear_color(0xaa, 0xaa, 0xaa);
		window.clear();

		for (auto &entity : entities) {
			auto &texture = entity->get_component_raw<Texture>();
			auto &transform = entity->get_component_raw<Transform>();

			SDL_Rect dstrect{
				.x = static_cast<int>(transform.position.x),
				.y = static_cast<int>(WINDOW_HEIGHT - transform.position.y - transform.scale.y),
				.w = static_cast<int>(transform.scale.x),
				.h = static_cast<int>(transform.scale.y),
			};

			window.render(texture, nullptr, &dstrect, 0.0, nullptr);
		}

		window.present();
	}
};

class PlayerSystem : public System {
   public:
	auto move(float delta) -> void {
		for (auto &entity : entities) {
			auto &transform = entity->get_component_raw<Transform>();
			auto &player = entity->get_component_raw<Player>();

			const auto keyboard_states = SDL_GetKeyboardState(nullptr);

			if (keyboard_states[SDL_SCANCODE_W])
				transform.position.y += player.speed * delta;
			if (keyboard_states[SDL_SCANCODE_A])
				transform.position.x -= player.speed * delta;
			if (keyboard_states[SDL_SCANCODE_S])
				transform.position.y -= player.speed * delta;
			if (keyboard_states[SDL_SCANCODE_D])
				transform.position.x += player.speed * delta;
		}
	}
};

class CollisionSystem : public System {
   public:
	auto update() {
		for (auto &entity : entities) {
			auto &transform = entity->get_component_raw<Transform>();
			auto &collider = entity->get_component_raw<Collider>();

			auto left = transform.position.x;
			auto right = transform.position.x + transform.scale.x;
			auto top = transform.position.y + transform.scale.y;
			auto bottom = transform.position.y;
			Vector2 center{(left + right) / 2.0f, (top + bottom) / 2.0f};

			// Walls
			if (left < 0) {
				transform.position.x = 0;
			}
			if (right > WINDOW_WIDTH) {
				transform.position.x = WINDOW_WIDTH - transform.scale.x;
			}
			if (bottom < 0) {
				transform.position.y = 0;
			}
			if (top > WINDOW_HEIGHT) {
				transform.position.y = WINDOW_HEIGHT - transform.scale.y;
			}

			// Other entities
			for (auto &other : entities) {
				if (entity->get_id() == other->get_id()) continue;

				auto &other_transform = other->get_component_raw<Transform>();
				auto &other_collider = other->get_component_raw<Collider>();
				auto other_left = other_transform.position.x;
				auto other_right = other_transform.position.x + other_transform.scale.x;
				auto other_top = other_transform.position.y + other_transform.scale.y;
				auto other_bottom = other_transform.position.y;
				Vector2 other_center{(other_left + other_right) / 2.0f, (other_top + other_bottom) / 2.0f};

				if (top <= other_bottom || bottom >= other_top || right <= other_left || left >= other_right) continue;

				// Points from other to this
				auto normal_vector = (other_center - center).normalize();
				constexpr auto NUDGE_STRENGTH = 1.0f;
				if (!collider.stationary)
					transform.position -= normal_vector * NUDGE_STRENGTH;
				if (!other_collider.stationary)
					other_transform.position += normal_vector * NUDGE_STRENGTH;
			}
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
	auto &collision_system = scene.create_system<CollisionSystem, Transform, Collider>();

	// Entities
	auto rick = scene.create_entity();
	rick->create_component<Transform>();
	rick->create_component<Texture>(window.load_image("assets/rick_astley.png"));
	rick->create_component<Player>();
	rick->create_component<Collider>();

	auto ball = scene.create_entity();
	auto &ball_transform = ball->create_component<Transform>();
	ball_transform.position = {300.0f, 300.0f};
	ball->create_component<Texture>(window.load_image("assets/ball.jpg"));
	ball->create_component<Collider>();

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
		while (now - prev_fixed >= FIXED_TIMESTEP_MS) {
			// Fixed update
			// fixed_update_system.update();
			prev_fixed += FIXED_TIMESTEP_MS;
		}

		// Variable loop/update
		auto delta = now - prev;
		prev = now;
		auto delta_s = delta / 1000.0f;
		// update_system.update(delta_s);
		player_system.move(delta_s);
		collision_system.update();

		// Render
		render_system.render(window);
	}
}