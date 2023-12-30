#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Core/Level.h"
#include "Core/Event System/EventHandler.h"
#include "Input/KeyboardEvents.h"
#include "Rendering/Materials/MaterialFactory.h"

using namespace Gem;

class Pong : public Level, public EventHandler<KeyboardEvents::KeyDown> {
public:
	Pong();
	~Pong() override;

	void HandleEvent(const KeyboardEvents::KeyDown& event) override;

	Pong(const Pong& other) = default;
	Pong(Pong&& other) noexcept = default;
	Pong& operator=(const Pong& other) = default;
	Pong& operator=(Pong&& other) noexcept = default;

	int leftScore{ };
	int rightScore{ };

	bool shouldQuit{ false };

	Entity leftPaddle{ DeadEntity };
	Entity rightPaddle{ DeadEntity };
	Entity ball{ DeadEntity };
	Entity camera{ DeadEntity };

	const int winningScore{ 10 };

private:
	SolidColour m_WhiteMaterial{ CreateMaterial(Colour::White) };

	void CreateEntities();
	void DeleteEntities();

	Entity CreatePaddle();
	void DeletePaddle(Entity paddle);

	Entity CreateBall();
	void DeleteBall(Entity ball);

	Entity CreateCamera();
	void DeleteCamera(Entity camera);
};