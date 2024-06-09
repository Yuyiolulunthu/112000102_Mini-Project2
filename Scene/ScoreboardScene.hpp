//
// Created by yuyio on 5/24/2024.
//

#ifndef SCOREBOARDONCLICK_HPP
#define SCOREBOARDONCLICK_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"

class ScoreboardScene final : public Engine::IScene {
private:
    std::string importedText;
    int currentPage = 1;
    int itemsPerPage = 10;

    std::vector<std::string> scores; // Declare scores here
    std::vector<std::pair<std::string, int>> scoreLines; // Declare scoreLines here

public:
    explicit ScoreboardScene() = default;
    /*int ScoreOut();
    static void ScoreIn(int score);*/
    void Initialize() override;
    void Terminate() override;
    void NextOnClick();
    void prevOnClick();
    void PlayOnClick(int stage);
    void LoadScores();
    void DisplayScores();
    void BackOnClick(int stage);

    static int myscores;

};
#endif //SCOREBOARDONCLICK_HPP
