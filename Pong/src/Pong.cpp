#include "Pong.h"
#include "CameraController.h"
#include "FPSCamera.h"
#include "Paddles.h"
#include "PaddlesSystem.h"

#include "Input/Keyboard.h"

#include "Physics/PhysicalProperties.h"
#include "Physics/Visualization/PhysicsVisualizationComponent.h"

#include "Rendering/Camera.h"
#include "Rendering/Renderer.h"
#include "Rendering/Materials/Material.h"
#include "Rendering/Meshes/Mesh.h"
#include "Utility/Transform.h"
#include "Utility/Utility.h"

using namespace Gem;

Pong::Pong() {
	CreateEntities();

	ecs.systemManager.AddSystem(PaddlesSystem);

	OpenGlContext::Get().clearColour = Colour::Black;

	ecs.systemManager.AddSystem([&](EntityComponentSystem& ecs) {
		auto& transform = ecs.componentManager.GetComponent<Transform>(ball);
		auto& properties = ecs.componentManager.GetComponent<PhysicalProperties>(ball);

		if (Keyboard::Get().GetKey(Key::Y)) {
			properties.netForce += Vector3f::east * 0.5f;
		}

		Renderer::Get().debug.Add(transform.position, transform.position + properties.velocity);
	});
}

Pong::~Pong() {
	DeleteEntities();
}

void Pong::HandleEvent(const KeyboardEvents::KeyDown& event) {
	if (event.key == Key::ESCAPE) {
		shouldQuit = true;
	}
}

void Pong::CreateEntities() {
	leftPaddle = CreatePaddle();
	ecs.componentManager.GetComponent<Transform>(leftPaddle).position.x = -15;
	ecs.componentManager.GetComponent<Transform>(leftPaddle).scale = { 0.4f, 3.0f, 0.4f };
	ecs.componentManager.AddComponent<LeftPaddle>(leftPaddle);

	rightPaddle = CreatePaddle();
	ecs.componentManager.GetComponent<Transform>(rightPaddle).position.x = 15;
	ecs.componentManager.GetComponent<Transform>(rightPaddle).scale = { 0.4f, 3.0f, 0.4f };
	ecs.componentManager.AddComponent<RightPaddle>(rightPaddle);

	ball = CreateBall();

	camera = CreateCamera();
}

void Pong::DeleteEntities() {
	DeleteCamera(camera);

	DeleteBall(ball);

	DeletePaddle(rightPaddle);
	DeletePaddle(leftPaddle);
}

Entity Pong::CreatePaddle() {
	Entity paddle = ecs.entityManager.Create();
	ecs.componentManager.AddComponent<Transform>(paddle);
	ecs.componentManager.AddComponent<Mesh>(paddle);
	ecs.componentManager.AddComponent<Material>(paddle, m_WhiteMaterial);
	ecs.componentManager.AddComponent<PhysicalProperties>(paddle);
	ecs.componentManager.AddComponent<PhysicsVisualizationComponent>(paddle, false, false, false);
	//ecs.componentManager.AddComponent<BoxCollider>(paddle);

	return paddle;
}

void Pong::DeletePaddle(Entity paddle) {
	//ecs.componentManager.RemoveComponent<BoxCollider>(paddle);
	ecs.componentManager.RemoveComponent<PhysicsVisualizationComponent>(paddle);
	ecs.componentManager.RemoveComponent<PhysicalProperties>(paddle);
	ecs.componentManager.RemoveComponent<Material>(paddle);
	ecs.componentManager.RemoveComponent<Mesh>(paddle);
	ecs.componentManager.RemoveComponent<Transform>(paddle);
}

Entity Pong::CreateBall() {
	ball = ecs.entityManager.Create();
	ecs.componentManager.AddComponent<Transform>(ball);
	ecs.componentManager.AddComponent<Mesh>(ball);
	ecs.componentManager.AddComponent<Material>(ball, m_WhiteMaterial);
	ecs.componentManager.AddComponent<PhysicalProperties>(ball);
	ecs.componentManager.AddComponent<PhysicsVisualizationComponent>(ball);
	//ecs.componentManager.AddComponent<BoxCollider>(ball);

	ecs.componentManager.GetComponent<Transform>(ball).scale = Vector3f{ 0.6f, 0.6f, 0.6f };
	ecs.componentManager.GetComponent<PhysicalProperties>(ball).velocity = Vector3f::east * ballSpeed;

	return ball;
}

void Pong::DeleteBall(Entity ball) {
	//ecs.componentManager.RemoveComponent<BoxCollider>(paddle);
	ecs.componentManager.RemoveComponent<PhysicsVisualizationComponent>(ball);
	ecs.componentManager.RemoveComponent<PhysicalProperties>(ball);
	ecs.componentManager.RemoveComponent<Material>(ball);
	ecs.componentManager.RemoveComponent<Mesh>(ball);
	ecs.componentManager.RemoveComponent<Transform>(ball);
	ecs.entityManager.Delete(ball);
}

Entity Pong::CreateCamera() {
	camera = ecs.entityManager.Create();
	ecs.componentManager.AddComponent<Camera>(camera);
	ecs.componentManager.AddComponent<Transform>(camera);

	ecs.componentManager.GetComponent<Transform>(camera).position.z = 25;
	ecs.componentManager.GetComponent<Transform>(camera).rotation.y = -90.0f;

	return camera;
}

void Pong::DeleteCamera(Entity camera) {
	ecs.componentManager.RemoveComponent<Transform>(camera);
	ecs.componentManager.RemoveComponent<Camera>(camera);
	ecs.entityManager.Delete(camera);
}
