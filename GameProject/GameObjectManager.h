#pragma once

#include "GameObject.h"

#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

class GameObjectManager
{
public:
	GameObjectManager();

	void drawAll(sf::RenderWindow& window);
	void updateAll(float timeDelta, const sf::Keyboard::Key& keyInput);
	void addObject(const std::string& name, GameObject* gameObject);
	int getObjectCount();
	GameObject* getObject(const std::string& name);
	void removeObject(const std::string& name);

private:
	std::map<std::string, std::unique_ptr<GameObject>> m_game_objects_map;
};

