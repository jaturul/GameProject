#include "stdafx.h"
#include "ApplicationController.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"

#include <SFML/Window/Event.hpp>

#include <cassert>
#include <iostream>

namespace
{
	const std::string SPLASH_SCREEN_PATH = "C:/Users/jatur/Documents/Visual Studio 2017/Projects/GameProject/GameProject/images/startScreen.jpg";
	const std::string MAIN_MENU_PATH = "C:/Users/jatur/Documents/Visual Studio 2017/Projects/GameProject/GameProject/images/mainMenuBackground.jpg";
	const int WINDOW_WIDTH = 1200;
	const int WINDOW_HEIGHT = 700;
}

ApplicationController::ApplicationController()
	: m_current_game_state(GameState::GameStateType::UNINITIALIZED)
	, m_splash_screen( new SplashScreen(SPLASH_SCREEN_PATH))
	, m_main_menu ( new MainMenu(MAIN_MENU_PATH, WINDOW_WIDTH, WINDOW_HEIGHT))
	, m_game ( new Game() ) 
{
	
}


ApplicationController::~ApplicationController()
{
}

int ApplicationController::startGame()
{
	assert(m_current_game_state == GameState::GameStateType::UNINITIALIZED);
	m_current_game_state = GameState::GameStateType::SPLASH_SCREEN;
	m_game_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game Window");

	return gameLoop();
}

int ApplicationController::gameLoop()
{
	while (m_game_window.isOpen())
	{
		switch (m_current_game_state)
		{
			case GameState::GameStateType::SPLASH_SCREEN:
			{
				m_splash_screen->run(m_game_window, m_current_game_state);
				break;
			}
			case GameState::GameStateType::MAIN_MENU:
			{
				m_main_menu->run(m_game_window, m_current_game_state);
				break;
			}
			case GameState::GameStateType::GAME:
			{
				m_game->run(m_game_window, m_current_game_state);
				break;
			}
			case GameState::GameStateType::EXIT:
			{
				m_game_window.close();
				break;
			}
		}
	}

	return 0;
}

