#include "PaddlesSystem.h"
#include "Paddles.h"

#include "Entity Component System/View.h"

#include "Input/Keyboard.h"
#include "Input/Keys.h"

#include "Utility/Time.h"
#include "Utility/Transform.h"

using namespace Gem;

constexpr float maxDistance = 12.0f;

void PaddlesSystem(EntityComponentSystem& ecs) {
	for (auto [ent, transform] : Gem::View<Transform>{ ecs }) {
		if (transform.position.y > maxDistance) {
			transform.position.y = maxDistance;
		}

		if (transform.position.y < -maxDistance) {
			transform.position.y = -maxDistance;
		}
	}

	const float speed = 8.0f * Time::deltaTime;

	for (auto [ent, transform, p] : Gem::View<Transform, LeftPaddle>{ ecs }) {
		if (Keyboard::Get().GetKey(Key::W)) {
			transform.position += Vector3f::up * speed;
		}

		if (Keyboard::Get().GetKey(Key::S)) {
			transform.position -= Vector3f::up * speed;
		}
	}

	for (auto [ent, transform, p] : Gem::View<Transform, RightPaddle>{ ecs }) {
		if (Keyboard::Get().GetKey(Key::UP)) {
			transform.position += Vector3f::up * speed;
		}

		if (Keyboard::Get().GetKey(Key::DOWN)) {
			transform.position -= Vector3f::up * speed;
		}
	}
}
