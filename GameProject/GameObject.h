#pragma once

#include <SFML/Graphics.hpp>
#include <string> 

class GameObject
{
public:
	GameObject(bool playerControllable, int windowWidth, int windowHeight);

	virtual void draw(sf::RenderWindow& window) = 0;
	
	bool isPlayerControllable();
	bool isImageLoaded();
	void loadImage(const std::string& filePath);

	sf::Rect<float> getBoundingBox();

	int getObjectWidth();
	int getObjectHeight();

	int getWindowWidth();
	int getWindowHeight();

	sf::Vector2f getPosition();
	void setPosition(float x, float y);

	virtual void update(float timeDelta) = 0;

protected:
	bool m_image_loaded;
	bool m_is_player_controllable;
	std::string m_image_path;

	sf::Texture m_object_texture;
	sf::Sprite m_object_sprite;

	int m_window_width;
	int m_window_height;

};

