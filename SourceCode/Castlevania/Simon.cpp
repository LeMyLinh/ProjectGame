#include "Simon.h"

Simon::Simon(TextureManager* textureM, Graphics* graphics, Input* input) : BaseObject(eID::SIMON)
{
	this->input = input;
	this->sprite = new Sprite();

	if (!this->sprite->initialize(graphics, textureM, SpriteManager::getInstance()))
	{
		throw GameError(GameErrorNS::FATAL_ERROR, "Can not init sprite character");
	}

	this->sprite->setPosition(GVector2(GAME_WIDTH / 2, GAME_HEIGHT / 2));
	this->setRect();

	currentAnimation = nullptr;
	walkingAnimation = new Animation(this->sprite, SIMON_BEHAVIOUR::walking, 1, 0.3f);
	fightingAnimation = new Animation(this->sprite, SIMON_BEHAVIOUR::fighting, 2, 0.3f);
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
	switch (this->status)
	{
	case eStatus::NORMAL:
	{
		this->sprite->setSpriteDataRect(SpriteManager::getInstance()->getSpritesData()[SIMON_BEHAVIOUR::front].rect);
		break;
	}
	case eStatus::DIEING:
	{
		this->sprite->setSpriteDataRect(SpriteManager::getInstance()->getSpritesData()[SIMON_BEHAVIOUR::dieing].rect);
		break;
	}
	case eStatus::JUMPING:
	{
		this->sprite->setSpriteDataRect(SpriteManager::getInstance()->getSpritesData()[SIMON_BEHAVIOUR::jump].rect);
		break;
	}
	default:
		break;
	}
}

void Simon::draw()
{
	this->sprite->draw();
}


void Simon::update(float dt)
{
	if (input->wasKeyPressed(VK_RIGHT))
	{
		this->setStatus(eStatus::WALKING);

		if (currentAnimation != nullptr)
			currentAnimation->stop();

		this->sprite->flipHorizontal(true);
		currentAnimation = walkingAnimation;
		currentAnimation->start();
	}
	if (input->wasKeyPressed(VK_LEFT))
	{
		this->setStatus(eStatus::WALKING);

		if (currentAnimation != nullptr)
			currentAnimation->stop();

		this->sprite->flipHorizontal(false);
		currentAnimation = walkingAnimation;
		currentAnimation->start();
	}
	if (input->wasKeyPressed(X_KEY))
	{
		this->setStatus(eStatus::JUMPING);
		if (currentAnimation != nullptr)
			currentAnimation->stop();

		this->setRect();
	}
	if (input->wasKeyPressed(VK_DOWN))
	{
		this->setStatus(eStatus::FIGHTING);

		if (currentAnimation != nullptr)
			currentAnimation->stop();

		currentAnimation = fightingAnimation;
		currentAnimation->start();
	}

	if (currentAnimation != nullptr)
	{
		currentAnimation->update(dt);
	}
}

void Simon::release()
{
	input = nullptr;
	sprite = nullptr;
	currentAnimation = nullptr;
	walkingAnimation = nullptr;
	fightingAnimation = nullptr;

	delete input, sprite, currentAnimation, walkingAnimation, fightingAnimation;
}