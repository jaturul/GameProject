#pragma once

#include <SFML/Graphics.hpp>

class GameState
{
public:
	enum class GameStateType { UNINITIALIZED = 0, SPLASH_SCREEN, MAIN_MENU, GAME, EXIT };

	GameState();

	virtual int run(sf::RenderWindow& window, GameStateType& nextGameState) = 0;

private:
	virtual void processEvent(sf::Event& event, GameStateType& nextGameStateType) = 0;
};