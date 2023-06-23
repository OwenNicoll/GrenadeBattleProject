#include "Screen.h"

Screen::Screen(Game* newGamePointer)
	:gamePointer(newGamePointer)
{
}

void Screen::Update(sf::Time frameTime)
{
}

void Screen::Draw(sf::RenderTarget& target)
{
}

std::string Screen::GetTag()
{
	return tag;
}

bool Screen::GetSwitchScreen()
{
	return switchScreen;
}
