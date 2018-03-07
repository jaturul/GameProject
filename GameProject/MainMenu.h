#pragma once

#include "GameState.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

class MainMenu : public GameState
{
public:

	enum class MenuOptionAction {NOTHING_SELECTED = -1, START, QUIT, NUMBER_OF_OPTIONS};

	struct Size
	{
		int width;
		int height;
	};

	struct MenuOption
	{
		sf::Texture m_menu_option_texture;
		sf::Sprite m_menu_option_sprite;

		sf::Rect<int> m_button_geometry;
		MenuOptionAction m_action_type;
	};

	MainMenu(const std::string& mainMenuImagePath, const int windowWidth, const int windowHeight);
	~MainMenu();

	virtual int run(sf::RenderWindow& window, GameStateType& nextGameState) override;

private:
	void addMenuOption(MenuOptionAction optionAction, int orderNumber, int maximumOptionWidth, int maximumOptionHeight, const std::string& optionImagePath);
	Size computeButtonSize(const int windowWidth, const int windowHeight, const int noOptions);
	MenuOptionAction handleClick(int x, int y);
	void initializeMenuOptions(int windowWidth, int windowHeight);
	virtual sf::Keyboard::Key processEvent(sf::Event& event, GameStateType& nextGameStateType) override;

	sf::Texture m_main_menu_background_texture;
	sf::Sprite m_main_menu_background_sprite;

	MenuOptionAction m_current_action;

	std::vector<std::unique_ptr<MenuOption>> m_menu_options;
};

