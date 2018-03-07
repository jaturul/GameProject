#pragma once
#include "GameState.h"

#include <SFML/Graphics.hpp>

#include <string>

class SplashScreen: public GameState
{
public:
	enum class EventProcessingOutcome {NOTHING = 0, KEY_PRESSED};

	SplashScreen( const std::string& splashScreenPath );
	~SplashScreen();

	virtual int run(sf::RenderWindow& window, GameStateType& nextGameStateType) override;

private:
	virtual sf::Keyboard::Key processEvent(sf::Event& event, GameStateType& nextGameStateType) override;

	sf::Texture m_splash_screen_texture;
	sf::Sprite m_splash_screen_sprite;
};

