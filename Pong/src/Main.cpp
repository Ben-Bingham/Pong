#include <iostream>
#include "Core/Engine.h"
#include "Utility/Log.h"

int main() {
	Gem::Engine engine{};

	engine.eventSystem.Distribute();

	std::cin.get();
}