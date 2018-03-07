#include "stdafx.h"
#include "SplashScreen.h"


SplashScreen::SplashScreen(const std::string& splashScreenPath )
{
	m_splash_screen_texture.loadFromFile(splashScreenPath);
	m_splash_screen_sprite.setTexture(m_splash_screen_texture);
}


SplashScreen::~SplashScreen()
{
}

int SplashScreen::run(sf::RenderWindow & window, GameStateType& nextGameStateType)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		processEvent(event, nextGameStateType);
		window.clear();
		window.draw(m_splash_screen_sprite);
		window.display();
	}

	return 0;
}

sf::Keyboard::Key SplashScreen::processEvent( sf::Event& event, GameStateType& nextGameStateType)
{
	if (event.type == sf::Event::KeyPressed)
	{
		nextGameStateType = GameStateType::MAIN_MENU;
		
		return event.key.code;
	}

	return sf::Keyboard::Unknown;
}