#include "Pong.h"
#include "Core/Engine.h"
#include "Core/Game.h"
#include "Core/Event System/EventSystem.h"
#include "Utility/Utility.h"

int main() {
	Path::SetGemAssets("../dependencies/Gemstone");

	Engine engine{}; // TODO can the engine init the main subsystems, but they be accessd staticly?

	Game game{ };

	auto level = CreatePtr<Pong>(engine);

	game.Run(level, [](Ptr<Level> level)->bool {
		const Ptr<Pong> pongLevel = std::reinterpret_pointer_cast<Pong, Level>(level);
		const int score = pongLevel->winningScore;

		return pongLevel->leftScore < score || pongLevel->rightScore < score;
	});
}