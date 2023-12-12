#include <iostream>
#include "Core/Engine.h"
#include "Utility/Log.h"

int main() {
	Gem::Engine engine{};
	LOG("X: " + std::to_string(engine.window.size.x) + ", Y:" + std::to_string(engine.window.size.y));
	std::cin.get();
}