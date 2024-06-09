#ifndef ICE_BULLET_HPP
#define ICE_BULLET_HPP

#include "Bullet.hpp"
class Turret;

class IceBullet : public Bullet {
public:
    IceBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void OnExplode(Enemy* enemy) override;
};

#endif // ICE_BULLET_HPP