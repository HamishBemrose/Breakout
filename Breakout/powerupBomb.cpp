#include "powerupBomb.h"

PowerupBomb::PowerupBomb(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos)
	: PowerupBase(window, paddle, ball, x_pos)
{
	_sprite.setFillColor(bombBallEffectsColour);
}

PowerupBomb::~PowerupBomb()
{
	int* pInteger = new int();

	if (pInteger != nullptr)
	{
		// use my pointer to do things.
	}

}

std::pair<POWERUPS, float> PowerupBomb::applyEffect()
{
	_ball->setVelocity(0.0f, 1.f); // Stop the ball for a second
	_ball->setBombBall(1.f); // Activate bomb effect for 1 second

	return { bombBall, 1.0f };
}
