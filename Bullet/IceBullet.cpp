//
// Created by yuyio on 5/27/2024.
//
#include <allegro5/base.h>
#include <random>
#include <string>

#include "UI/Animation/DirtyEffect.hpp"
#include "Enemy/Enemy.hpp"
#include "IceBullet.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

IceBullet::IceBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
 Bullet("play/bullet-10.png", 500, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
    // Replace "bullet-2.png" with your actual bullet image file
}

void IceBullet::OnExplode(Enemy* enemy) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
    getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
    // Replace "dirty-2.png" with your actual explosion effect image file
}