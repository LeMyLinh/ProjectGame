#include "Castlevania.h"
#include "ObjectManager.h"
#include "Collision.h"

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
	textureManager->onLostDevice();
	spriteManager->releaseAll();


	tileset->onLostDevice();
	delete mapInfo;
	delete mapLevel5;

	delete simon;

	delete whiteSkeleton;

	ObjectManager::getInstance()->release();
	Collision::getInstance()->release();
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
	if (!textureManager->initialize(graphics, SOURCE_IMAGE))
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
		throw GameError(GameErrorNS::FATAL_ERROR, "Can not initalize map level5");
	}

	camera = new Camera(GAME_WIDTH, GAME_HEIGHT);
	//camera->setPosition(VECTOR2(768 + 4 * 32,640 + 176/2));
	//camera->setPosition(VECTOR2(880, 832));
	camera->setPosition(VECTOR2(896, 778));

	mapLevel5->setCamera(camera);

	simon = new Simon(textureManager, graphics, input);
	simon->setCamera(this->camera);
	//simon->setPosition(VECTOR2(880, 832));

	whiteSkeleton = new WhiteSkeleton(textureManager, graphics);
}

void Castlevania::update(float dt)
{
	simon->update(dt);

	whiteSkeleton->setTarget(VECTOR2(simon->getPosition().x + simon->getSprite()->getWidth() * 0.5f, simon->getPosition().y));
	whiteSkeleton->update(dt);

	//camera->setPosition(simon->getPosition());
	this->camera->update(dt);
}

void Castlevania::handleInput(float dt)
{
	simon->handleInput(dt);
}

void Castlevania::collisions(float dt)
{
	simon->handleInput(dt);

	ObjectManager::getInstance()->onCheckCollision(simon, dt);
}

void Castlevania::render()
{
	this->getGraphics()->spriteBegin();
	mapLevel5->draw();
	simon->draw();
		

	whiteSkeleton->draw();

	this->getGraphics()->spriteEnd();
}

void Castlevania::releaseAll()
{
	GameManager::releaseAll();
}

void Castlevania::resetAll()
{
	GameManager::resetAll();
}

HWND Castlevania::getCurrentHWND()
{
	return this->hwnd;
}