#include "Game.h"
#include "Ball.h"
#include "PlayerPaddle.h"

namespace
{
	const std::string GAME_SCREEN_PATH = "C:/Users/jatur/Documents/Visual Studio 2017/Projects/GameProject/GameProject/images/gameScreen.jpg";
	const std::string PLAYER_PADDLE_IMAGE_PATH = "C:/Users/jatur/Documents/Visual Studio 2017/Projects/GameProject/GameProject/images/paddle.jpg";
	const std::string BALL_IMAGE_PATH = "C:/Users/jatur/Documents/Visual Studio 2017/Projects/GameProject/GameProject/images/ball.jpg";

	const float MAX_PADDLE_VELOCITY = 600.0f;
	const float MAX_BALL_VELOCITY = 90.0f;
	const float PADDLE_ACCELERATION = 3.0f;
}

Game::Game(int windowWidth, int windowHeight)
	: m_current_player_action(Game::PlayerAction::NONE)
	, m_window_width(windowWidth)
	, m_window_height(windowHeight)
{
	PlayerPaddle* player_paddle = new PlayerPaddle(MAX_PADDLE_VELOCITY, PADDLE_ACCELERATION, m_window_width, m_window_height, true); // owned by m_game_object_manager
	player_paddle->loadImage(PLAYER_PADDLE_IMAGE_PATH);
	player_paddle->setPosition(m_window_width / 2 - player_paddle->getObjectWidth() / 2, m_window_height - player_paddle->getObjectHeight());
	m_game_object_manager.addObject("PlayerPaddle", player_paddle);

	Ball* ball = new Ball(MAX_BALL_VELOCITY, false, m_window_width, m_window_height);
	ball->loadImage(BALL_IMAGE_PATH);
	ball->setPosition(m_window_width / 2 , m_window_height / 2 );
	m_game_object_manager.addObject("Ball", ball);
	
	m_game_texture.loadFromFile(GAME_SCREEN_PATH);
	m_game_sprite.setTexture(m_game_texture);
}

int Game::run(sf::RenderWindow & window, GameStateType& nextGameStateType)
{
	sf::Event event;
	sf::Keyboard::Key key_input;
	while (window.pollEvent(event))
	{
		 key_input = processEvent(event, nextGameStateType);
	}

	window.clear();
	m_game_object_manager.updateAll(0.02f, key_input);
	m_game_object_manager.drawAll(window);
	window.display();

	return 0;
}

sf::Keyboard::Key Game::processEvent(sf::Event & event, GameStateType& nextGameStateType)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			nextGameStateType = GameStateType::MAIN_MENU;
		}
		
		return event.key.code;
	}

	return sf::Keyboard::Unknown;
}
