#include "stdafx.h"
#include "PlayerPaddle.h"

#include <iostream>

PlayerPaddle::PlayerPaddle(float maxVelocity, int windowWidth, int windowHeight, bool playerControllable)
	: GameObject(playerControllable, windowWidth, windowHeight)
	, m_max_velocity(maxVelocity)
	, m_current_velocity(0.0f)
{
}

void PlayerPaddle::draw(sf::RenderWindow & window)
{
	window.draw(m_object_sprite);
}

void PlayerPaddle::update(float timeDelta)
{
	if (m_is_moving)
	{
		float position_delta = timeDelta * m_current_velocity;

		float new_position_x = m_object_sprite.getPosition().x + position_delta;

		setPosition(new_position_x, getPosition().y);
	}
}

void PlayerPaddle::processPlayerInput(float timeDelta, const sf::Keyboard::Key & keyInput)
{
	if (keyInput == sf::Keyboard::Left)
	{
		m_current_velocity = -m_max_velocity;
		m_is_moving = true;
	}
	else if (keyInput == sf::Keyboard::Right)
	{
		m_current_velocity = m_max_velocity;

		m_is_moving = true;
	}
	else
	{
		m_current_velocity = 0.0f;
		m_is_moving = false;
	}
}
