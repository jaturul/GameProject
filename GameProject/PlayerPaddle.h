#pragma once
#include "GameObject.h"

#include <SFML/Graphics.hpp>

class PlayerPaddle : public GameObject
{
public:
	PlayerPaddle(float maxVelocity,  float paddleAcceleration, int windowWidth, int windowHeight, bool playerControllable);
	
	virtual void draw(sf::RenderWindow& window) override;
	virtual void update(float timeDelta) override;

	void processPlayerInput(float timeDelta, const sf::Keyboard::Key& keyInput);

private:
	sf::Rect<int> m_paddle_geometry;
	
	bool m_is_moving;
	float m_current_velocity;
	float m_paddle_acceleration;
	float m_max_velocity;
};

