#include "Simon.h"
#include "SimonStateManager.h"

Simon::Simon(TextureManager* textureM, Graphics* graphics, Input* input) : BaseObject(eID::SIMON)
{
	this->input = input;
	this->sprite = new Sprite();

	if (!this->sprite->initialize(graphics, textureM, SpriteManager::getInstance()))
	{
		throw GameError(GameErrorNS::FATAL_ERROR, "Can not init sprite character");
	}

	this->sprite->setPosition(GVector2(0, 0));
	
	//currentAnimation = nullptr;
	//standingAnimation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->stand, FRAME_NUM_SIMON_STAND, false);
	walkingAnimation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->walking, FRAME_NUM_SIMON_TURN_RIGHT, 0.3f);
	fightingAnimation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->fighting, FRAME_NUM_SIMON_FIGHTING, 0.3f);

	SimonStateManager::getInstance()->init(this, input);
}

Simon::Simon()
{
	this->sprite = new Sprite();
}

Simon::~Simon()
{
	this->release();
}


void Simon::setRect()
{
	//switch (this->status)
	//{
	//case eStatus::NORMAL:
	//{
	//	this->sprite->setSpriteDataRect(SpriteManager::getInstance()->getSpritesData()[IndexOfSpriteSheet::getInstance()->front].rect);
	//	break;
	//}
	//case eStatus::DIEING:
	//{
	//	this->sprite->setSpriteDataRect(SpriteManager::getInstance()->getSpritesData()[IndexOfSpriteSheet::getInstance()->dieing].rect);
	//	break;
	//}
	//case eStatus::JUMPING:
	//{
	//	this->sprite->setSpriteDataRect(SpriteManager::getInstance()->getSpritesData()[IndexOfSpriteSheet::getInstance()->jump].rect);
	//	break;
	//}
	//default:
	//	break;
	//}

	this->sprite->setSpriteDataRect(SpriteManager::getInstance()->getSpritesData()[IndexOfSpriteSheet::getInstance()->stand].rect);

}

void Simon::draw()
{
	if (this->camera)
		this->sprite->setTransformCamera(VECTOR2(GAME_WIDTH*0.5f - camera->getPosition().x, GAME_HEIGHT*0.8f - camera->getPosition().y));
	
	this->sprite->draw();
}

void Simon::handleInput(float dt)
{
	updateDirection();

	SimonStateManager::getInstance()->getCurrentState()->handleInput(dt);
}


void Simon::update(float dt)
{
	//if (input->wasKeyPressed(VK_RIGHT))
	//{
	//	this->setStatus(eStatus::WALKING);

	//	if (currentAnimation != nullptr)
	//		currentAnimation->stop();

	//	this->sprite->flipHorizontal(true);
	//	currentAnimation = walkingAnimation;
	//	currentAnimation->start();
	//}
	//if (input->wasKeyPressed(VK_LEFT))
	//{
	//	this->setStatus(eStatus::WALKING);

	//	if (currentAnimation != nullptr)
	//		currentAnimation->stop();

	//	this->sprite->flipHorizontal(false);
	//	currentAnimation = walkingAnimation;
	//	currentAnimation->start();
	//}
	//if (input->wasKeyPressed(X_KEY))
	//{
	//	this->setStatus(eStatus::JUMPING);
	//	if (currentAnimation != nullptr)
	//		currentAnimation->stop();

	//	this->setRect();
	//}
	//if (input->wasKeyPressed(VK_DOWN))
	//{
	//	this->setStatus(eStatus::FIGHTING);

	//	if (currentAnimation != nullptr)
	//		currentAnimation->stop();

	//	currentAnimation = fightingAnimation;
	//	currentAnimation->start();
	//}

	//if (currentAnimation != nullptr)
	//{
	//	currentAnimation->update(dt);
	//}

	SimonStateManager::getInstance()->getCurrentState()->update(dt);
}

void Simon::release()
{
	input = nullptr;
	sprite = nullptr;
	//currentAnimation = nullptr;
	walkingAnimation = nullptr;
	fightingAnimation = nullptr;

	delete input, sprite, walkingAnimation, fightingAnimation;
}
void Simon::updateDirection()
{
	if (input->isKeyDown(VK_RIGHT))
	{
		this->setDirection(eDirection::right);
	}

	if (input->isKeyDown(VK_LEFT))
	{
		this->setDirection(eDirection::left);
	}
}

void Simon::running(float dt)
{

}

void Simon::turnUp()
{
}

void Simon::jump()
{
}

Animation * Simon::getStartingAnim()
{
	return this->walkingAnimation;
}

void Simon::setCamera(Camera * cam)
{
	this->camera = cam;
}