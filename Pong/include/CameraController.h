#pragma once
#include "Input/Mouse.h"
#include "Math/Vector.h"

struct CameraController {
	Gem::Vector2i oldMousePosition{Gem::Mouse::Get().GetPosition() };

	Gem::Vector3f up{ Gem::Vector3f::up };
	Gem::Vector3f right{ cross(Gem::Vector3f::north, up) };
};