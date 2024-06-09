// [main.cpp]
// This is the entry point of your game.
// You can register your scenes here, and start the game.
#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/LoseScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Scene/StageSelectScene.hpp"
#include "Scene/WinScene.hpp"
#include "Scene/StartScene.h"
#include "Scene/StartScene.hpp"
#include "Scene/SettingsScene.hpp"
#include "Scene/ScoreboardScene.hpp"
#include "Engine/AudioHelper.hpp"
std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;

int main(int argc, char **argv) {



	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();
	game.AddNewScene("settings", new SettingsScene());
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("win", new WinScene());
	game.AddNewScene("StageSelectScene", new StageSelectScene());
	game.AddNewScene("StartScene", new StartScene());
	game.AddNewScene("ScoreboardScene", new ScoreboardScene());
	//game.Start("stage-select", 60, 1600, 832);
	game.Start("StartScene", 60, 1600, 832);
	return 0;
}
