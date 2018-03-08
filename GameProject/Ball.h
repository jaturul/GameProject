#pragma once
#include "GameObject.h"

class GameObjectManager;

class Ball : public GameObject
{
public:
	Ball(const GameObjectManager* gameObjectManager, float velocityAmplitude, bool playerControllable, int windowWidth, int windowHeight);
	~Ball();

	virtual void update(float deltaTime) override;
	virtual void draw(sf::RenderWindow& window) override;

private:
	float getAngleForCollisions();
	float getAngleForPlayerCollisions();
	float getAngleForWallCollisions();

	const GameObjectManager* m_game_object_manager;
	float m_velocity_amplitude;
	float m_velocity_angle_radians;
};

