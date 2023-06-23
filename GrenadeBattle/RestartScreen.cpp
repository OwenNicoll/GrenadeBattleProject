#include "RestartScreen.h"
#include "MenuPanel.h"
#include "AssetManager.h"

#include <iostream>
#include <fstream>

RestartScreen::RestartScreen(Game* newGamePointer)
	:Screen(newGamePointer)
	,panel(nullptr)
	,titleText()
	,restartText()
{
	switchScreen = false;
	tag = "Menu";
	panel = new MenuPanel();


	font = AssetManager::RequestFont("Assets/dogica.ttf");
	
	titleText.setFont(font);
	titleText.setString("Game Over");
	titleText.setCharacterSize(40);
	titleText.setFillColor(sf::Color::Black);
	titleText.setPosition(770, 400);

	restartText.setFont(font);
	restartText.setString("Press X to Restart");
	restartText.setCharacterSize(24);
	restartText.setFillColor(sf::Color::Black);
	restartText.setPosition(750, 600);

}

void RestartScreen::Update(sf::Time frameTime)
{
	panel->Update(frameTime);

	if (sf::Joystick::isButtonPressed(0, sf::Joystick::Z) || sf::Joystick::isButtonPressed(1, sf::Joystick::Z))
	{
		switchScreen = true;
	}
}

void RestartScreen::Draw(sf::RenderTarget& target)
{
	panel->Draw(target);

	target.setView(target.getDefaultView());

	target.draw(titleText);
	target.draw(restartText);
}
