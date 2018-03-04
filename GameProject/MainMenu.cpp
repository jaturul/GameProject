#include "stdafx.h"
#include "MainMenu.h"
#include <iostream>

namespace
{
	const std::string START_BUTTON_IMAGE_PATH = "C:/Users/jatur/Documents/Visual Studio 2017/Projects/GameProject/GameProject/images/startButton.jpg";
	const std::string EXIT_BUTTON_IMAGE_PATH = "C:/Users/jatur/Documents/Visual Studio 2017/Projects/GameProject/GameProject/images/exitButton.jpg";
}


MainMenu::MainMenu(const std::string& mainMenuImagePath, const int windowWidth, const int windowHeight)
{
	m_main_menu_background_texture.loadFromFile(mainMenuImagePath);
	m_main_menu_background_sprite.setTexture(m_main_menu_background_texture);

	initializeMenuOptions(windowWidth, windowHeight);
}

MainMenu::~MainMenu()
{
}

int MainMenu::run(sf::RenderWindow & window, GameStateType & nextGameState)
{
	m_current_action = MenuOptionAction::NOTHING_SELECTED;
	sf::Event event;
	while (window.pollEvent(event))
	{
		processEvent(event, nextGameState);
	}

	window.clear();
	window.draw(m_main_menu_background_sprite);
	for (auto& option : m_menu_options)
	{
		window.draw(option->m_menu_option_sprite);
	}
	window.display();

	return 0;
}

void MainMenu::initializeMenuOptions(int windowWidth, int windowHeight)
{
	Size maximum_button_size = computeButtonSize(windowWidth, windowHeight, static_cast<int>(MenuOptionAction::NUMBER_OF_OPTIONS));

	addMenuOption(MenuOptionAction::START, 0, maximum_button_size.width, maximum_button_size.height, START_BUTTON_IMAGE_PATH);
	addMenuOption(MenuOptionAction::QUIT,  1, maximum_button_size.width, maximum_button_size.height, EXIT_BUTTON_IMAGE_PATH);
}

void MainMenu::addMenuOption(MainMenu::MenuOptionAction actionType, int orderNumber, int maximumOptionWidth, int maximumOptionHeight, const std::string& optionImagePath)
{
	// Load the option's sprite and texture
	std::unique_ptr<MenuOption> new_option = std::unique_ptr<MenuOption>(new MenuOption());
	new_option->m_menu_option_texture.loadFromFile(optionImagePath);
	new_option->m_menu_option_sprite.setTexture(new_option->m_menu_option_texture);

	// Set the position for the option's sprite
	int positionXWithMargin = (maximumOptionWidth - new_option->m_menu_option_texture.getSize().x) / 2;
	int positionYWithMargin = orderNumber * maximumOptionHeight + (maximumOptionHeight - new_option->m_menu_option_texture.getSize().y) / 2;
	new_option->m_menu_option_sprite.setPosition(static_cast<float>(positionXWithMargin), static_cast<float>(positionYWithMargin));
	
	// Set the position for the logical button
	new_option->m_button_geometry.left = positionXWithMargin;
	new_option->m_button_geometry.top = positionYWithMargin;
	new_option->m_button_geometry.width = new_option->m_menu_option_texture.getSize().x;
	new_option->m_button_geometry.height = new_option->m_menu_option_texture.getSize().y;

	new_option->m_action_type = actionType;

	m_menu_options.emplace_back(std::move(new_option));
}

MainMenu::Size  MainMenu::computeButtonSize(const int windowWidth, const int windowHeight, const int noOptions)
{
	Size button_size;
	button_size.width = windowWidth;
	button_size.height = windowHeight / noOptions;

	return button_size;
}

MainMenu::MenuOptionAction MainMenu::handleClick(int x, int y)
{
	for (auto& option : m_menu_options)
	{
		if (option->m_button_geometry.contains(x, y))
		{
			return option->m_action_type;
		}
	}

	return MainMenu::MenuOptionAction::NOTHING_SELECTED;
}

void MainMenu::processEvent(sf::Event & event, GameStateType & nextGameStateType)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		m_current_action = handleClick(event.mouseButton.x, event.mouseButton.y);

		if (m_current_action == MenuOptionAction::START)
		{
			nextGameStateType = GameStateType::GAME;
		}
		else if (m_current_action == MenuOptionAction::QUIT)
		{
			nextGameStateType = GameStateType::EXIT;
		}
	}
}

