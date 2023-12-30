#include "FPSCamera.h"
#include "Entity Component System/View.h"
#include "Input/Keyboard.h"
#include "Rendering/Camera.h"
#include "Utility/Time.h"
#include "Utility/Transform.h"
#include "CameraController.h"
#include "Entity Component System/EntityComponentSystem.h"

using namespace Gem;

void FPSCameraSystem(EntityComponentSystem& ecs) {
	 for (auto [ent, cam, transform, camController] : View<Camera, Transform, CameraController>(ecs)) {
		 const float speed = 10.0f * Time::deltaTime;

		 if (Keyboard::Get().GetKey(Key::W)) {
			 transform.position += cam.forward.normalize() * speed;
		 }

		 if (Keyboard::Get().GetKey(Key::S)) {
			 transform.position -= cam.forward.normalize() * speed;
		 }

		 if (Keyboard::Get().GetKey(Key::A)) {
			 transform.position -= cross(cam.forward.normalize(), Vector3f::up) * speed;
		 }

		 if (Keyboard::Get().GetKey(Key::D)) {
			 transform.position += cross(cam.forward.normalize(), Vector3f::up) * speed;
		 }

		 if (Keyboard::Get().GetKey(Key::SPACE)) {
			 transform.position += Vector3f::up * speed;
		 }

		 if (Keyboard::Get().GetKey(Key::LEFT_SHIFT)) {
			 transform.position -= Vector3f::up * speed;
		 }

		 const Vector2i mousePos = Mouse::Get().GetPosition();

		 Vector2f deltaMousePosition{ (float)mousePos.x - (float)camController.oldMousePosition.x, (float)camController.oldMousePosition.y - (float)mousePos.y };

		 constexpr float mouseSens = 0.05f;
		 deltaMousePosition *= mouseSens;

		 transform.rotation.y += deltaMousePosition.x;
		 transform.rotation.x += deltaMousePosition.y;

		 if (transform.rotation.x > 89.9f) {
			 transform.rotation.x = 89.9f;
		 }
		 else if (transform.rotation.x < -89.9f) {
			 transform.rotation.x = -89.9f;
		 }

		 camController.oldMousePosition = mousePos;

		 Vector3f forward;
		 forward.x = std::cos(degreesToRadians(transform.rotation.y)) * std::cos(degreesToRadians(transform.rotation.x));
		 forward.y = std::sin(degreesToRadians(transform.rotation.x));
		 forward.z = std::sin(degreesToRadians(transform.rotation.y)) * std::cos(degreesToRadians(transform.rotation.x));
		 cam.forward = forward.normalize();

		 camController.right = cross(cam.forward, Vector3f::up).normalize();
		 camController.up = cross(camController.right, cam.forward).normalize();
	 }
}