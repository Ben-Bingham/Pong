#pragma once
#include "Core/Level.h"

#include "..\..\dependencies\Gemstone\include\Rendering\Camera.h"
#include "Rendering/Meshes/Mesh.h"
#include "Rendering/Materials/Material.h"
#include "Rendering/Materials/MaterialFactory.h"
#include "Rendering/Materials/SolidColour.h"

#include "Utility/Transform.h"

using namespace Gem;

class Pong : public Level {
public:
	Pong() {
		InitEntities();
	}

	~Pong() {
		DeletePaddle(leftPaddle);
		ecs.entityManager.Delete(leftPaddle);

		DeletePaddle(rightPaddle);
		ecs.entityManager.Delete(rightPaddle);

		//ecs.componentManager.RemoveComponent<BoxCollider>(paddle);
		ecs.componentManager.RemoveComponent<Material>(ball);
		ecs.componentManager.RemoveComponent<Mesh>(ball);
		ecs.componentManager.RemoveComponent<Transform>(ball);
		ecs.entityManager.Delete(ball);
	}

	Pong(const Pong& other) = default;
	Pong(Pong&& other) noexcept = default;
	Pong& operator=(const Pong& other) = default;
	Pong& operator=(Pong&& other) noexcept = default;

	int leftScore;
	int rightScore;

	Entity leftPaddle{ DeadEntity };
	Entity rightPaddle{ DeadEntity };
	Entity ball{ DeadEntity };
	Entity camera{ DeadEntity };

	const int winningScore{ 10 };

private:
	SolidColour m_WhiteMaterial{ CreateMaterial(Colour::White) };

	void InitEntities() {
		leftPaddle = ecs.entityManager.Create();
		InitPaddle(leftPaddle);

		rightPaddle = ecs.entityManager.Create();
		InitPaddle(rightPaddle);

		ball = ecs.entityManager.Create();
		ecs.componentManager.AddComponent<Transform>(ball);
		ecs.componentManager.AddComponent<Mesh>(ball);
		ecs.componentManager.AddComponent<Material>(ball, m_WhiteMaterial);
		//ecs.componentManager.AddComponent<BoxCollider>(ball);

		camera = ecs.entityManager.Create();
		ecs.componentManager.AddComponent<Camera>(camera);
		ecs.componentManager.AddComponent<Transform>(camera);

		ecs.componentManager.GetComponent<Transform>(camera).position.z = 5;
	}

	void InitPaddle(Entity paddle) {
		ecs.componentManager.AddComponent<Transform>(paddle);
		ecs.componentManager.AddComponent<Mesh>(paddle);
		ecs.componentManager.AddComponent<Material>(paddle, m_WhiteMaterial);
		//ecs.componentManager.AddComponent<BoxCollider>(paddle);
	}

	void DeletePaddle(Entity paddle) {
		//ecs.componentManager.RemoveComponent<BoxCollider>(paddle);
		ecs.componentManager.RemoveComponent<Material>(paddle);
		ecs.componentManager.RemoveComponent<Mesh>(paddle);
		ecs.componentManager.RemoveComponent<Transform>(paddle);
	}
};