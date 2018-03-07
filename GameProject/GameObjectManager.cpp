#include "stdafx.h"
#include "GameObjectManager.h"
#include "PlayerPaddle.h"


GameObjectManager::GameObjectManager()
{
}

void GameObjectManager::drawAll(sf::RenderWindow& window)
{
	for (auto& nameAndObjectPair : m_game_objects_map)
	{
		nameAndObjectPair.second->draw(window);
	}
}

void GameObjectManager::updateAll(float timeDelta, const sf::Keyboard::Key& keyInput)
{
	for (auto& name_object_pair : m_game_objects_map)
	{
		if (name_object_pair.second->isPlayerControllable())
		{
			if (PlayerPaddle* player_paddle = dynamic_cast<PlayerPaddle*>(name_object_pair.second.get()))
			{
				player_paddle->processPlayerInput(0.02f, keyInput);
			}
		}

		name_object_pair.second->update(0.02f);
	}
}

void GameObjectManager::addObject(const std::string & name, GameObject * gameObject)
{
	std::unique_ptr<GameObject> new_game_object = std::unique_ptr<GameObject>(gameObject);

	m_game_objects_map.insert({ name,std::move(new_game_object) });
}

int GameObjectManager::getObjectCount()
{
	return static_cast<int>(m_game_objects_map.size());
}

GameObject * GameObjectManager::getObject(const std::string & name)
{
	if (m_game_objects_map.find(name) == m_game_objects_map.end())
	{
		return nullptr;
	}
	return m_game_objects_map[name].get();
}

void GameObjectManager::removeObject(const std::string & name)
{
	auto element_to_remove = m_game_objects_map.find(name);
	if (element_to_remove != m_game_objects_map.end())
	{
		element_to_remove->second.reset();
		m_game_objects_map.erase(element_to_remove);
	}
	
}
