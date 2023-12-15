#include "Pong.h"
#include <iostream>
#include "Core/Engine.h"
#include "Core/Game.h"

int main() {
	Engine engine{};

	Game game{ engine };

	auto level = CreatePtr<Pong>();

	game.Run(level, [](Ptr<Level> level)->bool {
		const Ptr<Pong> pongLevel = std::reinterpret_pointer_cast<Pong, Level>(level);
		const int score = pongLevel->winningScore;

		return pongLevel->leftScore < score || pongLevel->rightScore < score;
	});
}