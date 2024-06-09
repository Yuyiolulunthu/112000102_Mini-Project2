#include <functional>
#include <string>
#include <allegro5/allegro_color.h> // Ensure Allegro color functions are included
#include <allegro5/allegro_font.h>
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Input.hpp"
#include "UI/Component/input.hpp" // Include InputBox header
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "WinScene.hpp"

#include <iostream>
#include <ostream>

#include "Engine/Resources.hpp"
#include <fstream>
#include <iostream>
#include <ctime>

#include "ScoreboardScene.hpp"


void WinScene::Initialize() {
    ticks = 0;
    playerName = "";

    font = al_load_font("pirulen.ttf", 24, 0); // Load the font
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));

    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

    font = al_load_font("pirulen.ttf", 24, 0); // Load the font
    playerName = "";
    bgmId = AudioHelper::PlayAudio("win.wav");
    // ...

    inputField = std::make_unique<Engine::TextInput>("pirulen.ttf", 24, halfW, halfH - 250, 300, 50, 255, 255, 255, 255, 0, 0, 0, 255, 0.5, 0.5);
    // ...
}

void WinScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}

void WinScene::Update(float deltaTime) {
    ticks = ScoreboardScene::myscores;
    IScene::Update(deltaTime);


    // Update logic for TextInput if needed
    ALLEGRO_EVENT event;
    while (!al_is_event_queue_empty(event_queue)) {

        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
            if(event.keyboard.keycode==ALLEGRO_KEY_ENTER) {
                std::time_t curretTime = std::time(nullptr);
                std::tm* localTime = std::localtime(&curretTime);
                playerName = inputField->GetText();
                std::ofstream file;
                file.open("Resource/scoreboard.txt", std::ios_base::app);
                file << "\n" << playerName << " " << ticks << " " << localTime->tm_year + 1900 << "/" << localTime->tm_mon + 1 << "/" << localTime->tm_mday << " " << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec;
                file.close();


                Engine::GameEngine::GetInstance().ChangeScene("StageSelectScene");
                Engine::GameEngine::GetInstance().ChangeScene("ScoreboardScene");
            }
            inputField->OnKeyPress(event.keyboard.keycode);
        }
    }

}

void WinScene::Draw() const {
    IScene::Draw();
    inputField->Draw(); // Add this line to draw the input field
    //al_draw_text(Engine::Resources::GetInstance().GetFont("pirulen.ttf", 36).get(), al_map_rgb(255, 255, 255), 20, 20, 0, std::to_string(ticks).c_str());
}
void WinScene::BackOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("StartScene");
}