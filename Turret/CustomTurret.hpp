//
// Created by yuyio on 5/27/2024.
//

#ifndef CUSTOMTURRET_HPP
#define CUSTOMTURRET_HPP


#include "CustomTurret.hpp"

class CustomTurret: public Turret {
public:
    static const int Price;
    CustomTurret(float x, float y);
    void CreateBullet() override;
};

#endif //CUSTOMTURRET_HPP
