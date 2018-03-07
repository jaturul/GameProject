#pragma once

#include "GameObjectManager.h"
#include "GameState.h"
#include "PlayerPaddle.h"

#include <SFML/Graphics.hpp>

#include <memory>

class Game: public GameState
{
public:
	enum class PlayerAction{NONE = -1, MOVE_LEFT, MOVE_RIGHT};
	Game(int windowWidth, int windowHeight);

	virtual int run(sf::RenderWindow& window, GameStateType& nextGameStateType) override;

private:
	virtual sf::Keyboard::Key processEvent(sf::Event& event, GameStateType& nextGameStateType) override;

	GameObjectManager m_game_object_manager;

	PlayerAction m_current_player_action;
	sf::Texture m_game_texture;
	sf::Sprite m_game_sprite;

	int m_window_width;
	int m_window_height;
};

