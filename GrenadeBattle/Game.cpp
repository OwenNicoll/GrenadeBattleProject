#include "Game.h"
#include "Screen.h"
#include "LevelScreen.h"
#include "RestartScreen.h"

Game::Game()
	: window(sf::VideoMode::getDesktopMode(), "Grenade Battle", sf::Style::Titlebar | sf::Style::Close)
	, gameClock()
	, currentScreen(nullptr)
{
	// Window setup
	window.setMouseCursorVisible(false);

	// TODO: Setup screens
	currentScreen = new LevelScreen(this);

	//currentScreen = new RestartScreen(this);
}

void Game::RunGameLoop()
{
	// Repeat as long as the window is open
	while (window.isOpen())
	{
		Update();
		Draw();
		EventHandling();
	}

}

void Game::SwitchScreen()
{
	std::cout << "SwitchScreen being called" << std::endl;

	if (currentScreen->GetTag() == "Level")
	{
		currentScreen = new RestartScreen(this);
	}

	else if (currentScreen->GetTag() == "Menu")
	{
		currentScreen = new LevelScreen(this);
	}
}

void Game::EventHandling()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		// Close the game if escape is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
	}
}

void Game::Update()
{
	sf::Time frameTime = gameClock.restart();

	// Update current screen
	if (currentScreen != nullptr)
		currentScreen->Update(frameTime);

	if (currentScreen->GetSwitchScreen() == true)
	{
		SwitchScreen();
	}

}

void Game::Draw()
{
	window.clear();

	// Draw current screen
	if (currentScreen != nullptr)
		currentScreen->Draw(window);

	window.display();
}

sf::RenderWindow& Game::GetRenderWindow()
{
	return window;
}
