#pragma once
#include <SFML/Graphics.hpp>

class Screen;

class Game
{

public:

	Game();

	void RunGameLoop();

	void SwitchScreen();

	void EventHandling();
	void Update();
	void Draw();

	sf::RenderWindow& GetRenderWindow();


private:

	sf::RenderWindow window;
	sf::Clock gameClock;

	Screen* currentScreen;

};

