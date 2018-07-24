#include "Castlevania.h"



Castlevania::Castlevania()
{
	this->spriteManager = SpriteManager::getInstance();
	this->textureManager = new TextureManager();

	this->tileset = new TextureManager();
	this->mapInfo = new MapInfo();
	this->mapLevel5 = new Map();
}


Castlevania::~Castlevania()
{
	delete simon;
	textureManager->onLostDevice();
	spriteManager->releaseAll();

	tileset->onLostDevice();
	delete mapInfo;
	delete mapLevel5;
}

Castlevania* Castlevania::instance = nullptr;
Castlevania * Castlevania::getInstance()
{
	if (instance == nullptr)
		instance = new Castlevania();

	return instance;
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
	if (!tileset->initialize(graphics, TILESET_LV5_IMAGE))
	{
		throw GameError(GameErrorNS::FATAL_ERROR, "Can not load tileset");
	}

	if (!mapInfo->initialize(MAP_LEVEL5))
	{
		throw GameError(GameErrorNS::FATAL_ERROR, "Can not load map info");
	}

	if (!mapLevel5->initialize(graphics, tileset, mapInfo))
	{
		throw GameError(GameErrorNS::FATAL_ERROR, "Can not initalize map brinstar");
	}

	camera = new Camera(GAME_WIDTH, GAME_HEIGHT +48);
	//camera->setPosition(VECTOR2(768 + 4 * 32,640 + 176/2));
	//camera->setPosition(VECTOR2(0, 0));

	mapLevel5->setCamera(camera);

	simon = new Simon(textureManager, graphics, input);
	simon->setCamera(this->camera);
	//simon->setPosition(VECTOR2(864, 800));
}

void Castlevania::update(float dt)
{
	simon->update(dt);

	camera->setPosition(simon->getPosition());
}

void Castlevania::ai()
{

}

void Castlevania::collisions()
{

}

void Castlevania::render()
{
	mapLevel5->draw();
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