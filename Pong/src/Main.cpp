#include "Core/Engine.h"
#include "CameraController.h"
#include "Pong.h"
#include "Core/Game.h"
#include "Core/Window.h"
#include "Core/Event System/EventSystem.h"
#include "Input/Keyboard.h"
#include "Utility/Utility.h"
#include "Entity Component System/View.h"
#include "Input/Mouse.h"

#include "Rendering/Camera.h"
#include "Rendering/Materials/Material.h"
#include "Rendering/Meshes/Mesh.h"

#include "Utility/Transform.h"

class TestLevel : public Level {
public:
	TestLevel() {
		//ScreenSpace screenSpaceMat = CreatePtr<ScreenSpace_>();
		SolidColour solidColourMat = CreateMaterial(Colour::Blue);

		quarter = ecs.entityManager.Create();
		ecs.componentManager.AddComponent<Transform>(quarter);
		ecs.componentManager.AddComponent<Material>(quarter, solidColourMat);
		ecs.componentManager.AddComponent<Mesh>(quarter, Cube{ });

		camera = ecs.entityManager.Create();
		ecs.componentManager.AddComponent<Transform>(camera);
		ecs.componentManager.AddComponent<Camera>(camera);
		ecs.componentManager.AddComponent<CameraController>(camera);

		Window::Get().DisableCursor();

		ecs.systemManager.AddSystem([](EntityComponentSystem& ecs) {
			for (auto [ent, cam, transform, camController] : View<Camera, Transform, CameraController>(ecs)) {
				constexpr float speed = 0.5f; // TODO delta time

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
		});
	}

	~TestLevel() {
		ecs.componentManager.RemoveComponent<CameraController>(camera);
		ecs.componentManager.RemoveComponent<Camera>(camera);
		ecs.componentManager.RemoveComponent<Transform>(camera);
		ecs.entityManager.Delete(camera);

		ecs.componentManager.RemoveComponent<Mesh>(quarter);
		ecs.componentManager.RemoveComponent<Material>(quarter);
		ecs.componentManager.RemoveComponent<Transform>(quarter);
		ecs.entityManager.Delete(quarter);
	}

	Entity quarter{ DeadEntity };
	Entity camera{ DeadEntity };
};

int main() {
	Path::SetGemAssets("../dependencies/Gemstone");

	Engine engine{ };

	Game game{ };

	/*auto level = CreatePtr<TestLevel>();

	game.Run(level);*/

	auto level = CreatePtr<Pong>();

	game.Run(level, [](const Ptr<Level>& level)->bool {
		const Ptr<Pong> pongLevel = std::static_pointer_cast<Pong, Level>(level);
		const int score = pongLevel->winningScore;

		if (pongLevel->shouldQuit) {
			return false;
		}

		return pongLevel->leftScore < score || pongLevel->rightScore < score;
	});
}