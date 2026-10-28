#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);

    // Create bricks in the level
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    

    if (_lives <= 0)
    {
        _masterText.setString("Game over.");
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.");
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);

	updateShake(dt); // Update the screen shake effect
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    //initiates screen shake when life lost. this lasts .2 seconds with am offset of 8px
	startShake(0.2f, 8.f, sf::Vector2f(0.f,0.f));
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

//ADDITIONS
void GameManager::startShake(float duration, float magnitude, sf::Vector2f direction)
{
	_shakeTimer = duration;
	_shakeMagnitude = magnitude;

	//normilise directoion in order to apply shake in a non horizantal direction
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0.f) 
    {
        shakeDirection = direction / length;
    }
    else
    {
		shakeDirection = sf::Vector2f(0.f, 0.f); // Default to no direction if the input is zero
    }
}

void GameManager::updateShake(float dt)
{
	// If the shake timer is active, apply the shake effect
    if (_shakeTimer > 0.f) {

		//shake time goes down so its not infinite
		_shakeTimer -= dt;

        if (shakeDirection.x ==0.f && shakeDirection.y == 0.f) {

            // If no specific direction is provided, apply random shake
            float offsetX = (static_cast<float>(std::rand()) / RAND_MAX * 2.f - 1.f) * _shakeMagnitude;
            float offsetY = (static_cast<float>(std::rand()) / RAND_MAX * 2.f - 1.f) * _shakeMagnitude;

            // Apply the shake effect by modifying the view's center
            gameView.setCenter(_originalCenter + sf::Vector2f(offsetX, offsetY));
        }
        else {
            // Apply shake in the specified direction
			float offsetX = (shakeDirection.x / RAND_MAX * 2.f - 1.f) * _shakeMagnitude;    
            float offsetY = (shakeDirection.y / RAND_MAX * 2.f - 1.f) * _shakeMagnitude;

            gameView.setCenter(_originalCenter + shakeDirection * _shakeMagnitude);
		}
    }

    else {
		gameView.setCenter(_originalCenter); // Reset to the original center when shake is done
    }

	_window->setView(gameView);

}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
