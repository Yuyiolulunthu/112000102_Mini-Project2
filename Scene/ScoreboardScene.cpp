//
// Created by yuyio on 5/24/2024.
//

#include "StartScene.h"
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "Scene/ScoreboardScene.hpp"
#include "Scene/StageSelectScene.hpp"
#include "Scene/SettingsScene.hpp"
#include "Scene/StartScene.h"
#include "StageSelectScene.hpp"
#include <algorithm> // For std::find_if and std::sort
#include <sstream> // For std::istringstream
#include <vector>
#include <algorithm>
#include <fstream>


void ScoreboardScene::PlayOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("PlayScene");
}
void ScoreboardScene::Initialize() {
    LoadScores();

    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;
    LoadScores();
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 0));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Scoreboard", "pirulen.ttf", 48, halfW, halfH / 4, 10, 155, 155, 155, 0.5, 0.5));



    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 300, halfH * 3 / 2 - 50, 400, 100);





    btn->SetOnClickCallback(std::bind(&ScoreboardScene::NextOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next Page", "pirulen.ttf", 48, halfW + 500, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    //Next Part

    btn =  new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 700, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::prevOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Prev Page", "pirulen.ttf", 48, halfW - 500, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    std::ifstream inputFile("Resource/scoreboard.txt");

    if (inputFile) {
        std::getline(inputFile, importedText, '\0'); // Read the entire file
        inputFile.close();
    } else {
        // Handle error
    }
    AddNewObject(new Engine::Label(importedText, "pirulen.ttf", 48, halfW, halfH, 0, 0, 0, 255, 0.5, 0.5));

    DisplayScores();


}

void ScoreboardScene::LoadScores() {
    std::ifstream file("Resource/scoreboard.txt");
    std::string line;
    std::vector<std::pair<std::string, int>> scoreLines; // Store lines and their last number

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        int lastNumber = 0;

        // Extract tokens and find the last number
        while (iss >> token) {
            try {
                lastNumber = std::stoi(token);
            } catch (std::invalid_argument&) {
                // Skip non-integer tokens
            }
        }
        scoreLines.emplace_back(line, lastNumber);
    }
    file.close();

    // Sort based on the number

    std::sort(scoreLines.begin(), scoreLines.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return b.second < a.second;
    });

    // Store sorted lines in the scores vector
    scores.clear();
    for (const auto& scoreLine : scoreLines) {
        scores.push_back(scoreLine.first);
    }
    //printf("len=%d\n", static_cast<int>(scores.size()));
}

void ScoreboardScene::DisplayScores() {


    int start = (currentPage - 1) * itemsPerPage;
    int end = std::min(static_cast<int>(scores.size()), currentPage * itemsPerPage);
    printf("%d %d\n", static_cast<int>(scores.size()), end);
    int y = 100;

    for (int i = start; i < end; ++i) {
        auto label = new Engine::Label(scores[i], "pirulen.ttf", 30, 700, y + 150, 255, 255, 255, 255, 0.5, 0.5);
        AddNewObject(label);
        y += 30;

    }
}



void ScoreboardScene::NextOnClick() {
    int totalPages = (scores.size() + itemsPerPage - 1) / itemsPerPage;
    if (currentPage < totalPages) {
        currentPage++;
    }
    else{
        currentPage = 1;
    }
    printf("page %d\n", currentPage);
    Engine::GameEngine::GetInstance().ChangeScene("StageSelectScene");
    Engine::GameEngine::GetInstance().ChangeScene("ScoreboardScene");
}

void ScoreboardScene::prevOnClick() {
    int totalPages = (scores.size() + itemsPerPage - 1) / itemsPerPage;
    if (currentPage == 1) {
        currentPage = totalPages;
    }
    else {
        currentPage--;
    }
    Engine::GameEngine::GetInstance().ChangeScene("StageSelectScene");
    Engine::GameEngine::GetInstance().ChangeScene("ScoreboardScene");
}




void ScoreboardScene::Terminate() {

    IScene::Terminate();
    // Clear scores vector and scene objects
    scores.clear();
    Clear();
}
void ScoreboardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("StageSelectScene");

}


