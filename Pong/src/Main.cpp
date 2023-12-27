#include "Pong.h"
#include "Core/Engine.h"
#include "Core/Game.h"
#include "Core/Event System/EventSystem.h"

#include "Rendering/Geometry/Quarter.h"
#include "Rendering/Materials/ScreenSpace.h"

#include "Utility/Utility.h"

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
		ecs.componentManager.AddComponent<Camera_New>(camera);
	}

	~TestLevel() {
		ecs.componentManager.RemoveComponent<Camera_New>(camera);
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

	game.Run(level, [](Ptr<Level> level)->bool {
		const Ptr<Pong> pongLevel = std::reinterpret_pointer_cast<Pong, Level>(level);
		const int score = pongLevel->winningScore;

		return pongLevel->leftScore < score || pongLevel->rightScore < score;
	});
}