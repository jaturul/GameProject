#pragma once

#include "GameState.h"

#include <SFML/Graphics.hpp>

#include <memory>

class SplashScreen;
class Game;
class MainMenu;

class ApplicationController
{
	
public:
	ApplicationController();
	~ApplicationController();

	int startGame();

private:
	int gameLoop();

	sf::RenderWindow m_game_window;
	GameState::GameStateType m_current_game_state;
	std::unique_ptr<SplashScreen> m_splash_screen;
	std::unique_ptr<MainMenu> m_main_menu;
	std::unique_ptr<Game> m_game;
};

