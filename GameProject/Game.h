#pragma once

#include "GameState.h"

#include <SFML/Graphics.hpp>

class Game: public GameState
{
public:
	Game();

	virtual int run(sf::RenderWindow& window, GameStateType& nextGameStateType) override;

private:
	virtual void processEvent(sf::Event& event, GameStateType& nextGameStateType) override;

	sf::Texture m_game_texture;
	sf::Sprite m_game_sprite;
};

