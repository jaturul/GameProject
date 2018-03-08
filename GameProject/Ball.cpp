#include "stdafx.h"
#include "Ball.h"
#include "GameObjectManager.h"
#include "PlayerPaddle.h"


#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <cassert>
#include <iostream>

namespace
{
	const float M_PI_float = static_cast<float>(M_PI);
	const float COMPARISON_ACCURACY = 0.1;
}

Ball::Ball(const GameObjectManager* gameObjectManager, float velocityAmplitude, bool playerControllable, int windowWidth, int windowHeight)
	: GameObject(playerControllable, windowWidth, windowHeight)
	, m_velocity_amplitude(velocityAmplitude)
	, m_game_object_manager(gameObjectManager)
{
	srand(time(NULL));
	int angle_in_degrees = 100 + (rand() % 150);
	std::cout << "angle in degrees: " << angle_in_degrees << std::endl;
	float angle_in_radians = 2.0f * M_PI * angle_in_degrees / 360.0f;
	std::cout << "angle in radians: " << angle_in_radians << std::endl;
	m_velocity_angle_radians = angle_in_radians;
}


Ball::~Ball()
{
}

void Ball::update(float deltaTime)
{
	m_velocity_angle_radians = getAngleForCollisions();

	float velocity_x = m_velocity_amplitude * sin(m_velocity_angle_radians);
	float velocity_y = m_velocity_amplitude * cos(m_velocity_angle_radians);

	setPosition(getPosition().x + deltaTime * velocity_x , getPosition().y + deltaTime * velocity_y);
}

void Ball::draw(sf::RenderWindow & window) 
{
	window.draw(m_object_sprite);
}

float Ball::getAngleForCollisions()
{
	float new_velocity_angle_radians = getAngleForPlayerCollisions();
	if (new_velocity_angle_radians != m_velocity_angle_radians)
	{
		return new_velocity_angle_radians;
	}

	new_velocity_angle_radians = getAngleForWallCollisions();
	if (new_velocity_angle_radians != m_velocity_angle_radians)
	{
		return new_velocity_angle_radians;
	}

	return m_velocity_angle_radians;	
}

float Ball::getAngleForPlayerCollisions()
{
	//TODO
	return m_velocity_angle_radians;
}

float Ball::getAngleForWallCollisions()
{
	if ((fabs(getPosition().y) <= COMPARISON_ACCURACY) ||
		(fabs(getPosition().y - m_window_height + getObjectHeight()) <= COMPARISON_ACCURACY)) // check vertical collisions
	{
		return M_PI_float - m_velocity_angle_radians;
	}
	else if ((fabs(getPosition().x) <= COMPARISON_ACCURACY) ||
		(fabs(getPosition().x - m_window_width + getObjectWidth()) < COMPARISON_ACCURACY)) // check horizontal collisions
	{
		return 2.0f * M_PI_float - m_velocity_angle_radians;
	}

	return m_velocity_angle_radians;
}
