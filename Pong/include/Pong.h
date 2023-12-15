#pragma once
#include "Core/Level.h"

#include "Rendering/Meshes/Mesh.h"

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

		//ecs.componentManager.RemoveComponent<ColourMaterial>(paddle, Colour::White);
		//ecs.componentManager.RemoveComponent<CubeMesh>(paddle);
		//ecs.componentManager.RemoveComponent<BoxCollider>(paddle);
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

	const int winningScore{ 10 };

private:
	void InitEntities() {
		leftPaddle = ecs.entityManager.Create();
		InitPaddle(leftPaddle);

		rightPaddle = ecs.entityManager.Create();
		InitPaddle(rightPaddle);

		ball = ecs.entityManager.Create();
		ecs.componentManager.AddComponent<Transform>(ball);
		//ecs.componentManager.AddComponent<CubeMesh>(ball);
		//ecs.componentManager.AddComponent<BoxCollider>(ball);
		//ecs.componentManager.AddComponent<ColourMaterial>(ball, Colour::White);
	}

	void InitPaddle(Entity paddle) {
		ecs.componentManager.AddComponent<Transform>(paddle);
		ecs.componentManager.AddComponent<Mesh>(paddle);
		//ecs.componentManager.AddComponent<BoxCollider>(paddle);
		//ecs.componentManager.AddComponent<ColourMaterial>(paddle, Colour::White);
	}

	void DeletePaddle(Entity paddle) {
		//ecs.componentManager.RemoveComponent<ColourMaterial>(paddle, Colour::White);
		//ecs.componentManager.RemoveComponent<BoxCollider>(paddle);
		//ecs.componentManager.RemoveComponent<CubeMesh>(paddle);
		ecs.componentManager.RemoveComponent<Transform>(paddle);

	}
};