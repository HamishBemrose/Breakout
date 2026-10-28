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
	_ball->setVelocity(0.0f, 2.5f); // Stop the ball
	_ball->setBombBall(2.5f); // Activate bomb effect for 5 seconds

	return { bombBall, 2.5f };
}
