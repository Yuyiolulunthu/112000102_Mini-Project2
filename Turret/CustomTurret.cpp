//
// Created by yuyio on 5/27/2024.
//
#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/FireBullet.hpp"
#include "Bullet/IceBullet.hpp"
#include "Engine/Group.hpp"
#include "MachineGunTurret.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "CustomTurret.hpp"

const int CustomTurret::Price = 50;
CustomTurret::CustomTurret(float x, float y) :

Turret("play/tower-base.png", "play/turret-7.png", x, y, 200, Price, 0.5) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void CustomTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new IceBullet(Position + normalized * 36, diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}

