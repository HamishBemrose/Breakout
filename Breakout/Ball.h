#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
	void setBombBall(float duration); 

    void ballExplode(float dt);

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::Vector2f _centre;
    sf::RenderWindow* _window;
    float _velocity;
    float _radius;
    bool _isAlive;
    bool _isFireBall;
    bool _isBombBall;
    float _timeWithPowerupEffect;
    

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

