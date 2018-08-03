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
	camera->setPosition(VECTOR2(CAM_POS_X, CAM_POS_Y));

	ObjectManager::getInstance()->init(textureManager, graphics);

	if (!ObjectManager::getInstance()->load_list(OBJECT_LAYER_LEVEL5))
	{
		throw GameError(GameErrorNS::FATAL_ERROR, "Can not load object layer level5 json");
	}

	simon = new Simon(textureManager, graphics, input);
	//simon->setCamera(this->camera);
	//simon->setPosition(VECTOR2(880, 832));

	whiteSkeleton = new WhiteSkeleton(textureManager, graphics);
	//whiteSkeleton->setCamera(this->camera);
}

void Castlevania::update(float dt)
{
	simon->update(dt);

	whiteSkeleton->setTarget(VECTOR2(932, 798));
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
	//simon->handleInput(dt);

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