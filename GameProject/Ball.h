#pragma once
#include "GameObject.h"
class Ball :
	public GameObject
{
public:
	Ball(float velocityAmplitude, bool playerControllable, int windowWidth, int windowHeight);
	~Ball();

	virtual void update(float deltaTime) override;
	virtual void draw(sf::RenderWindow& window) override;

private:
	void checkCollisions();

	float m_coord_x;
	float m_coord_y;

	float m_velocity_amplitude;
	float m_velocity_angle_radians;
};

