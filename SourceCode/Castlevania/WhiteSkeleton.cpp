#include "WhiteSkeleton.h"



WhiteSkeleton::WhiteSkeleton()
{
}

WhiteSkeleton::WhiteSkeleton(TextureManager *texture, Graphics *graphics) : BaseObject(eID::WHITE_SKELETON)
{
	this->sprite = new Sprite();
	if (!this->sprite->initialize(graphics, texture, SpriteManager::getInstance()))
	{
		throw GameError(GameErrorNS::FATAL_ERROR, "Can not init sprite White Skeleton");
	}

	whiteAnimation = new Animation(this->sprite, IndexOfSpriteSheet::getInstance()->whiteSkeleton, 2, 0.2f);
	whiteAnimation->start();

	this->startPosition = VECTOR2(880, 798);
	this->target = VECTOR2ZERO;
	this->setPosition(this->startPosition);

	t = 0;
	timeDeath = 0;
}

WhiteSkeleton::~WhiteSkeleton()
{
	delete whiteAnimation;
}

void WhiteSkeleton::update(float dt)
{
	if (this->whiteAnimation != nullptr)
		this->whiteAnimation->update(dt);

	if (this->target != VECTOR2ZERO && this->isInStatus(eStatus::STANDING))
	{
		this->setStatus(eStatus::WALKING);
		this->whiteAnimation->setTimeFrameDelay(this->whiteAnimation->getTimeFrameDelay() * 0.5f);
	}

	if (this->isInStatus(eStatus::WALKING))
	{
		if (t < 1)
		{
			t += dt;
			this->setPosition((1 - t) * startPosition + t * target);
		}
	}
}

void WhiteSkeleton::draw()
{
	if (this->sprite != nullptr)
	this->sprite->draw();
}

void WhiteSkeleton::release()
{
	this->sprite = nullptr;
	this->whiteAnimation = nullptr;

	delete this->sprite;
	delete this->whiteAnimation;
}

VECTOR2 WhiteSkeleton::getTarget()
{
	return this->target;
}

void WhiteSkeleton::setTarget(VECTOR2 target)
{
	if (this->target != target && abs(target.x - this->startPosition.x) < GAME_WIDTH * 0.15f)
		this->target = target;
}