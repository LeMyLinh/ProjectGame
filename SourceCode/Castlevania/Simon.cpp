#include "Simon.h"
#include "SimonStateManager.h"
#include "Camera.h"

Simon::Simon(TextureManager* textureM, Graphics* graphics, Input* input) : BaseObject(eID::SIMON)
{
	this->input = input;
	this->sprite = new Sprite();

	if (!this->sprite->initialize(graphics, textureM, SpriteManager::getInstance()))
	{
		throw GameError(GameErrorNS::FATAL_ERROR, "Can not init sprite character");
	}

	this->sprite->setPosition(VECTOR2(864, 832));
	
	walkingAnimation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->walking, FRAME_NUM_SIMON_WALKING, 0.2f);
	fightingAnimation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->fighting, FRAME_NUM_SIMON_FIGHTING, 0.2f);
	upStairAnimation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->up_stair, FRAME_NUM_SIMON_UPSTAIR, 0.2f);
	downStairAnimation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->down_stair, FRAME_NUM_SIMON_DOWNSTAIR, 0.2f);
	up_fight_animation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->fight_up_stair, FRAME_NUM_SIMON_UP_FIGHT, 0.2f);
	down_fight_animation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->fight_down_stair, FRAME_NUM_SIMON_DOWN_FIGHT, 0.2f);
	sit_fight_animation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->fight_sit, FRAME_NUM_SIMON_SIT_FIGHT, 0.2f);
	
	//walkingAnimation = new Animation(this->sprite, VECTOR2(0,1.0f), IndexOfSpriteSheet::getInstance()->walking, FRAME_NUM_SIMON_WALKING, 0.3f);
	//fightingAnimation = new Animation(this->sprite, VECTOR2(0, 1.0f), IndexOfSpriteSheet::getInstance()->fighting, FRAME_NUM_SIMON_FIGHTING, 0.2f);
	//upStairAnimation = new Animation(this->sprite, VECTOR2(0, 1.0f), IndexOfSpriteSheet::getInstance()->up_stair, FRAME_NUM_SIMON_UPSTAIR, 0.2f);
	//downStairAnimation = new Animation(this->sprite, VECTOR2(0, 1.0f), IndexOfSpriteSheet::getInstance()->down_stair, FRAME_NUM_SIMON_DOWNSTAIR, 0.2f);
	//up_fight_animation = new Animation(this->sprite, VECTOR2(0, 1.0f), IndexOfSpriteSheet::getInstance()->fight_up_stair, FRAME_NUM_SIMON_UP_FIGHT, 0.2f);
	//down_fight_animation = new Animation(this->sprite, VECTOR2(0, 1.0f), IndexOfSpriteSheet::getInstance()->fight_down_stair, FRAME_NUM_SIMON_DOWN_FIGHT, 0.2f);
	//sit_fight_animation = new Animation(this->sprite, VECTOR2(0, 1.0f), IndexOfSpriteSheet::getInstance()->fight_sit, FRAME_NUM_SIMON_SIT_FIGHT, 0.2f);

	SimonStateManager::getInstance()->init(this, input);

	this->isFalling = false;
	this->moveHorizontal = true;
	this->moveLeft = true;
	this->moveRight = true;
	this->jump = true;
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


void Simon::draw()
{
	this->sprite->draw();
}

void Simon::handleInput(float dt)
{
	SimonStateManager::getInstance()->getCurrentState()->handleInput(dt);
	if (Camera::getInstance()->canFollowHorizon())
	{
		if ((input->isKeyUp(VK_LEFT) && input->isKeyUp(VK_RIGHT)) || (input->isKeyDown(VK_LEFT) && input->isKeyDown(VK_RIGHT)) || this->isInStatus(eStatus::STANDING))
			Camera::getInstance()->setVelocity(VECTOR2(this->getVelocity().x, 0));
	}
}


void Simon::update(float dt)
{
	if (Camera::getInstance()->canFollowHorizon())
	{
		if ((this->getPosition().x > Camera::getInstance()->getActiveArea().right) ||
			(this->getPosition().x < Camera::getInstance()->getActiveArea().left))
			Camera::getInstance()->setVelocity(VECTOR2(this->getVelocity().x, 0));
	}
	else
	{
		if ((this->getPosition().y > Camera::getInstance()->getActiveArea().top) ||
			(this->getPosition().y < Camera::getInstance()->getActiveArea().bottom))
			Camera::getInstance()->setVelocity(VECTOR2(0, this->getVelocity().y));
	}

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
//void Simon::updateDirection()
//{
//	if (input->isKeyDown(VK_RIGHT))
//	{
//		if (this->isInDirection(eDirection::left))
//		{
//			this->setScaleX(1);
//			this->setPositionX(this->getPosition().x - this->getSprite()->getWidth());
//			this->setDirection(eDirection::right);
//		}
//	}
//
//	if (input->isKeyDown(VK_LEFT))
//	{
//		if (this->isInDirection(eDirection::right))
//		{
//			this->setScaleX(-1);
//			this->setPositionX(this->getPosition().x - this->getSprite()->getWidth());
//			this->setDirection(eDirection::left);
//		}
//	}
//}

void Simon::updateHorizontal(float dt)
{
	this->setPosition(this->getPosition().x + velocity.x * dt, this->getPosition().y);
}

void Simon::updateVertical(float dt)
{
	//if (this->isFalling)
	//{
	//	this->setPosition(this->getPosition().x, this->getPosition().y + SIMON_VERLOCITY_Y * dt);
	//}
	//else
	//{
	//	totalJumpHeight += SIMON_VERLOCITY_Y * dt;

	//	if (totalJumpHeight <= MAX_JUMP)
	//		this->setPosition(this->getPosition().x, this->getPosition().y + SIMON_VERLOCITY_Y * dt * (-1));
	//	else
	//		this->setFall(true);
	//}

	this->setPosition(this->getPosition().x, this->getPosition().y + velocity.y * dt);
}

bool Simon::isFall()
{
	return this->isFalling;
}

bool Simon::canMoveleft()
{
	return moveLeft;
}

bool Simon::canMoveRight()
{
	return moveRight;
}

bool Simon::isJump()
{
	return jump;
}

void Simon::setFall(bool isFall)
{
	this->isFalling = isFall;
}

void Simon::setCanMoveRight(bool moveRight)
{
	this->moveRight = moveRight;
}

void Simon::setCanMoveLeft(bool moveLeft)
{
	this->moveLeft = moveLeft;
}

void Simon::setJump(bool jump)
{
	this->jump = jump;
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

void Simon::onCollision(BaseObject *object, float dt)
{
	SimonStateManager::getInstance()->getCurrentState()->onCollision(object, dt);
}