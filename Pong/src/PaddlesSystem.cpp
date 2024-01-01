#include "PaddlesSystem.h"
#include "Paddles.h"
#include "Entity Component System/View.h"
#include "Input/Keyboard.h"
#include "Input/Keys.h"
#include "Physics/PhysicalProperties.h"
#include "Rendering/Renderer.h"
#include "Utility/Transform.h"

using namespace Gem;

constexpr float maxDistance = 12.0f;

void PaddlesSystem(EntityComponentSystem& ecs) {
	for (auto [ent, transform, properties] : Gem::View<Transform, PhysicalProperties>{ ecs }) {
		if (transform.position.y > maxDistance) {
			transform.position.y = maxDistance;

			properties.acceleration = 0;
			properties.velocity = 0;
		}

		if (transform.position.y < -maxDistance) {
			transform.position.y = -maxDistance;

			properties.acceleration = 0;
			properties.velocity = 0;
		}
	}

	constexpr float speed = 8.0f;

	for (auto [ent, properties, p] : Gem::View<PhysicalProperties, LeftPaddle>{ ecs }) {
		if (Keyboard::Get().GetKey(Key::W)) {
			properties.velocity = Vector3f::up * speed;
		}
		else if (Keyboard::Get().GetKey(Key::S)) {
			properties.velocity = Vector3f::down * speed;
		}
		else {
			properties.velocity = 0;
		}
	}

	for (auto [ent, transform, properties, p] : Gem::View<Transform, PhysicalProperties, RightPaddle>{ ecs }) {
		if (Keyboard::Get().GetKey(Key::UP)) {
			properties.velocity = Vector3f::up * speed;
		}
		else if (Keyboard::Get().GetKey(Key::DOWN)) {
			properties.velocity = Vector3f::down * speed;
		}
		else {
			properties.velocity = 0;
		}
	}
}
