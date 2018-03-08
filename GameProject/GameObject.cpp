#include "stdafx.h"
#include "GameObject.h"

#include <iostream>

GameObject::GameObject(bool playerControllable, int windowWidth, int windowHeight)
	: m_is_player_controllable(playerControllable)
	, m_window_width(windowWidth)
	, m_window_height(windowHeight)
{
	
}

bool GameObject::isPlayerControllable() const
{
	return m_is_player_controllable;
}

bool GameObject::isImageLoaded() const
{
	return m_image_loaded;
}

int GameObject::getObjectWidth() const
{
	return m_object_texture.getSize().x;
}

int GameObject::getObjectHeight() const
{
	return m_object_texture.getSize().y;
}

int GameObject::getWindowWidth() const
{
	return m_window_width;
}

int GameObject::getWindowHeight() const
{
	return m_window_height;
}

sf::Vector2f GameObject::getPosition() const
{
	return m_object_sprite.getPosition();
}

void GameObject::loadImage(const std::string & imagePath)
{
	if (m_object_texture.loadFromFile(imagePath))
	{
		m_object_sprite.setTexture(m_object_texture);
		m_image_loaded = true;
		m_image_path = imagePath;
	}
	else
	{
		m_image_loaded = false;
		m_image_path = "";
	}
}

sf::Rect<float> GameObject::getBoundingBox() const
{
	int width = getObjectWidth();
	int height = getObjectHeight();

	return sf::Rect<float>(getPosition().x, getPosition().y, width, height);
}

void GameObject::setPosition(float x, float y)
{
	float truncated_x = std::min( std::max(x, 0.0f), static_cast<float>(m_window_width - m_object_texture.getSize().x) );
	float truncated_y = std::min( std::max(y, 0.0f), static_cast<float>(m_window_height - m_object_texture.getSize().y) );

	m_object_sprite.setPosition(truncated_x, truncated_y);
}

