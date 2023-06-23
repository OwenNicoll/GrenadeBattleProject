#include "Pip.h"
#include "AssetManager.h"

Pip::Pip()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/pip.png"));
	sprite.setScale(2, 2);
}
