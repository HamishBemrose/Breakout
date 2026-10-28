#pragma once
#include "PowerupBase.h"
class PowerupBomb : public PowerupBase
{
public:
    PowerupBomb(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos);
    ~PowerupBomb();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect

};

