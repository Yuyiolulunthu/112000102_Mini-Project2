#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <allegro5/allegro_audio.h>
#include "Engine/IScene.hpp"
#include <allegro5/allegro_font.h>
#include <memory>
#include "UI/Component/Input.hpp"

class WinScene final : public Engine::IScene {
private:
	int ticks;
	ALLEGRO_SAMPLE_ID bgmId;
	std::string playerName;
	ALLEGRO_FONT* font;
	ALLEGRO_EVENT_QUEUE* event_queue;
	std::unique_ptr<Engine::TextInput> inputField;


public:
	explicit WinScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void BackOnClick(int stage);
	void OnTextInput(const std::string& text);
	void Draw() const override;
};

#endif // WINSCENE_HPP
