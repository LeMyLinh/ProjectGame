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

	this->sprite->setPosition(VECTOR2(0, GAME_HEIGHT * 0.8));
	
	walkingAnimation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->walking, FRAME_NUM_SIMON_WALKING, 0.2f);
	fightingAnimation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->fighting, FRAME_NUM_SIMON_FIGHTING, 0.2f);
	upStairAnimation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->up_stair, FRAME_NUM_SIMON_UPSTAIR, 0.2f);
	downStairAnimation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->down_stair, FRAME_NUM_SIMON_DOWNSTAIR, 0.2f);
	up_fight_animation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->fight_up_stair, FRAME_NUM_SIMON_UP_FIGHT, 0.2f);
	down_fight_animation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->fight_down_stair, FRAME_NUM_SIMON_DOWN_FIGHT, 0.2f);
	sit_fight_animation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->fight_sit, FRAME_NUM_SIMON_SIT_FIGHT, 0.2f);
	
	
	SimonStateManager::getInstance()->init(this, input);
	this->isFalling = false;
	this->totalJumpHeight = 0;
}

Simon::Simon()
{
	this->sprite = new Sprite();
}

Simon::~Simon()
{
	this->release();
}


//void Simon::setRect()
//{
//	//switch (this->status)
//	//{
//	//case eStatus::NORMAL:
//	//{
//	//	this->sprite->setSpriteDataRect(SpriteManager::getInstance()->getSpritesData()[IndexOfSpriteSheet::getInstance()->front].rect);
//	//	break;
//	//}
//	//case eStatus::DIEING:
//	//{
//	//	this->sprite->setSpriteDataRect(SpriteManager::getInstance()->getSpritesData()[IndexOfSpriteSheet::getInstance()->dieing].rect);
//	//	break;
//	//}
//	//case eStatus::JUMPING:
//	//{
//	//	this->sprite->setSpriteDataRect(SpriteManager::getInstance()->getSpritesData()[IndexOfSpriteSheet::getInstance()->jump].rect);
//	//	break;
//	//}
//	//default:
//	//	break;
//	//}
//
//	this->sprite->setSpriteDataRect(SpriteManager::getInstance()->getSpritesData()[IndexOfSpriteSheet::getInstance()->stand].rect);
//
//}

void Simon::draw()
{
	//if (this->camera)
	//	this->sprite->setTransformCamera(VECTOR2(GAME_WIDTH*0.5f - camera->getPosition().x, GAME_HEIGHT*0.8f - camera->getPosition().y));
	
	this->sprite->draw();
}

void Simon::handleInput(float dt)
{
	//SimonStateManager::getInstance()->getCurrentState()->handleInput(dt);
	updateDirection();
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

	updateDirection();
	SimonStateManager::getInstance()->getCurrentState()->update(dt);
}

void Simon::release()
{
	input = nullptr;
	sprite = nullptr;
	walkingAnimation = nullptr;
	fightingAnimation = nullptr;
	upStairAnimation = nullptr;
	downStairAnimation = nullptr;
	up_fight_animation = nullptr;
	down_fight_animation = nullptr;
	sit_fight_animation = nullptr;

	delete input, sprite, walkingAnimation, fightingAnimation, upStairAnimation, downStairAnimation, up_fight_animation, down_fight_animation, sit_fight_animation;
}
void Simon::updateDirection()
{
	if (input->isKeyDown(VK_RIGHT))
	{
		if (this->isInDirection(eDirection::left))
		{
			this->setScaleX(-1);
			this->setPositionX(this->getPosition().x - this->getSprite()->getWidth());
			this->setDirection(eDirection::right);
		}
	}

	if (input->isKeyDown(VK_LEFT))
	{
		if (this->isInDirection(eDirection::right))
		{
			this->setScaleX(1);
			this->setPositionX(this->getPosition().x - this->getSprite()->getWidth());
			this->setDirection(eDirection::right);
		}
	}
}

void Simon::updateHorizontal(float dt)
{
	this->setPosition(this->getPosition().x + SIMON_VERLOCITY_X * dt*getDirection(), this->getPosition().y);
}

void Simon::updateVertical(float dt)
{
	if (this->isFalling)
	{
		this->setPosition(this->getPosition().x, this->getPosition().y + SIMON_VERLOCITY_Y * dt);
	}
	else
	{
		totalJumpHeight += SIMON_VERLOCITY_Y * dt * (-1);

		if (totalJumpHeight <= MAX_JUMP_HEIGHT)
			this->setPosition(this->getPosition().x, this->getPosition().y + SIMON_VERLOCITY_Y * dt * (-1));
		else
			this->setFall(true);
	}
}

bool Simon::isFall()
{
	return this->isFalling;
}

void Simon::setFall(bool isFall)
{
	this->isFalling = isFall;
}

Animation* Simon::getWalkingAnimation()
{
	return this->walkingAnimation;
}
Animation* Simon::getFightingAnimation()
{
	return this->fightingAnimation;
}
Animation* Simon::getUpStairAnimation()
{
	return this->upStairAnimation;
}
Animation* Simon::getDownStairAnimation()
{
	return this->downStairAnimation;
}
Animation* Simon::getUpFightAnimation()
{
	return this->up_fight_animation;
}
Animation* Simon::getDownFightAnimation()
{
	return this->down_fight_animation;
}
Animation* Simon::getSitFightAnimation()
{
	return this->sit_fight_animation;
}

void Simon::setCamera(Camera * cam)
{
	this->camera = cam;
}