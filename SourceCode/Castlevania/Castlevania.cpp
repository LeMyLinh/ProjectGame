#include "Castlevania.h"



Castlevania::Castlevania()
{
	this->spriteManager = SpriteManager::getInstance();
	this->textureManager = new TextureManager();
}


Castlevania::~Castlevania()
{
	delete simon;
	textureManager->onLostDevice();
	spriteManager->releaseAll();
}

void Castlevania::initialize(HWND hwnd)
{
	GameManager::initialize(hwnd);

	if (!spriteManager->initialize(SOURCE_JSON))
	{
		throw GameError(GameErrorNS::FATAL_ERROR, "Can not  load json");
	}
	if (!textureManager->initialize(graphics, SOURCE_IMAGE, 0, 0))
	{
		throw GameError(GameErrorNS::FATAL_ERROR, "Can not load image");
	}

	simon = new Simon(textureManager, graphics, input);
}

void Castlevania::update(float dt)
{
	simon->update(dt);
}

void Castlevania::ai()
{

}

void Castlevania::collisions()
{

}

void Castlevania::render()
{
	simon->draw();
}

void Castlevania::releaseAll()
{
	GameManager::releaseAll();
}

void Castlevania::resetAll()
{
	GameManager::resetAll();
}