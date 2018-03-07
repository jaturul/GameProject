#include "stdafx.h"
#include "Ball.h"


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

Ball::Ball(float velocityAmplitude, bool playerControllable, int windowWidth, int windowHeight)
	: GameObject(playerControllable, windowWidth, windowHeight)
	, m_velocity_amplitude(velocityAmplitude)
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
	checkCollisions();

	float velocity_x = m_velocity_amplitude * sin(m_velocity_angle_radians);
	float velocity_y = m_velocity_amplitude * cos(m_velocity_angle_radians);

	std::cout << "vel x = " << velocity_x << "; vel y = " << velocity_y << std::endl;

	/*std::cout << "coord x = " << getPosition().x + deltaTime * velocity_x << "; coord y = " << getPosition().y + deltaTime * velocity_y << std::endl;*/


	setPosition(getPosition().x + deltaTime * velocity_x , getPosition().y + deltaTime * velocity_y);
}

void Ball::draw(sf::RenderWindow & window) 
{
	window.draw(m_object_sprite);
}

void Ball::checkCollisions()
{
	// check vertical collisions
	if (fabs(m_coord_y) <= COMPARISON_ACCURACY)
	{
		std::cout << "Collision at (x = " << m_coord_x << ", y = 0??" << m_coord_y << "! current angle in radians: " << m_velocity_angle_radians << std::endl;
		/*assert((m_velocity_angle_radians > M_PI_float / 2.0f) && (m_velocity_angle_radians < 3.0f * M_PI_float / 2.0f));*/

		if( (m_velocity_angle_radians > M_PI_float / 2) && (m_velocity_angle_radians < M_PI_float) )
		{
			m_velocity_angle_radians -= M_PI_float / 2.0f;
			std::cout << "new velocity angle radians = " << m_velocity_angle_radians << std::endl;
		}
		else if ((m_velocity_angle_radians > M_PI_float) && (m_velocity_angle_radians < 3.0f * M_PI_float / 2.0f))
		{
			m_velocity_angle_radians += M_PI_float / 2.0f;
			std::cout << "new velocity angle radians = " << m_velocity_angle_radians << std::endl;
		}
	}
	else if (fabs(m_coord_y - m_window_height + getObjectHeight()) <= COMPARISON_ACCURACY )
	{
		std::cout << "Collision at (x =  " << m_coord_x << ", y = height - ball_height?? " << m_coord_y << "! current angle in radians: " << m_velocity_angle_radians << std::endl;
		/*assert(((m_velocity_angle_radians < M_PI_float / 2.0f) && (m_velocity_angle_radians >= 0.0f)) ||
			   ((m_velocity_angle_radians > 3.0f * M_PI_float / 2.0f) && (m_velocity_angle_radians <= 2.0f * M_PI_float)));*/

		if ((m_velocity_angle_radians <= M_PI_float / 2) && (m_velocity_angle_radians >= 0))
		{
			m_velocity_angle_radians += M_PI_float / 2.0f;
			std::cout << "new velocity angle radians = " << m_velocity_angle_radians << std::endl;
		}
		else if ((m_velocity_angle_radians >= 3.0f * M_PI_float / 2.0f) && (m_velocity_angle_radians <= 2.0f * M_PI_float ))
		{
			m_velocity_angle_radians -= M_PI_float / 2.0f;
			std::cout << "new velocity angle radians = " << m_velocity_angle_radians << std::endl;
		}
	}

	// check horizontal collisions
	if ( fabs(m_coord_x) <= COMPARISON_ACCURACY)
	{
		std::cout << "Collision at (x = 0?? " << m_coord_x << ", y = " << m_coord_y << "! current angle in radians: " << m_velocity_angle_radians << std::endl;
		/*assert((m_velocity_angle_radians > M_PI_float ) && (m_velocity_angle_radians < 2.0f * M_PI_float));*/

		if ((m_velocity_angle_radians > M_PI_float) && (m_velocity_angle_radians < 3.0f * M_PI_float / 2.0f))
		{
			m_velocity_angle_radians -= M_PI_float / 2.0f;
			std::cout << "new velocity angle radians = " << m_velocity_angle_radians << std::endl;
		}
		else if ((m_velocity_angle_radians > 3.0f * M_PI_float / 2.0f) && (m_velocity_angle_radians < 2.0f * M_PI_float))
		{
			m_velocity_angle_radians = -m_velocity_angle_radians + 2.0f * M_PI_float;
			std::cout << "new velocity angle radians = " << m_velocity_angle_radians << std::endl;
		}
	}
	else if ( fabs(m_coord_x - m_window_width + getObjectWidth()) < COMPARISON_ACCURACY)
	{
		std::cout << "Collision at (x = width - ball_width?? " << m_coord_x << ", y = " << m_coord_y << "! current angle in radians: " << m_velocity_angle_radians << std::endl;
		/*assert((m_velocity_angle_radians > 0.0f) && (m_velocity_angle_radians < M_PI_float ));*/

		if ( (m_velocity_angle_radians > 0) && (m_velocity_angle_radians < M_PI_float / 2.0f))
		{
			m_velocity_angle_radians = -m_velocity_angle_radians + 2 * M_PI_float;
			std::cout << "new velocity angle radians = " << m_velocity_angle_radians << std::endl;
		}
		else if ((m_velocity_angle_radians > M_PI_float / 2.0f) && (m_velocity_angle_radians < M_PI_float ))
		{
			m_velocity_angle_radians += M_PI_float / 2.0f;
			std::cout << "new velocity angle radians = " << m_velocity_angle_radians << std::endl;
		}
	}
}
