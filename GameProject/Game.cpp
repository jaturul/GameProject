#include "Game.h"

namespace
{
	const std::string GAME_SCREEN_PATH = "C:/Users/jatur/Documents/Visual Studio 2017/Projects/GameProject/GameProject/images/gameScreen.jpg";
}

Game::Game()
{
	m_game_texture.loadFromFile(GAME_SCREEN_PATH);
	m_game_sprite.setTexture(m_game_texture);
}

int Game::run(sf::RenderWindow & window, GameStateType& nextGameStateType)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		processEvent(event, nextGameStateType);

		window.clear();
		window.draw(m_game_sprite);
		window.display();
	}

	return 0;
}

void Game::processEvent(sf::Event & event, GameStateType& nextGameStateType)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		nextGameStateType = GameStateType::MAIN_MENU;
	}
}
