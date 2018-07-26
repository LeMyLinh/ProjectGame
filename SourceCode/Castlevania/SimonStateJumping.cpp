#include "SimonStateJumping.h"
#include "SimonStateManager.h"


SimonStateJumping::SimonStateJumping()
{
}

SimonStateJumping::SimonStateJumping(Simon * simon, Input * input) : BaseState(simon, input)
{
}

SimonStateJumping::~SimonStateJumping()
{
	jumpFightAnim = nullptr;
	delete jumpFightAnim;
}

void SimonStateJumping::init()
{
	if (input->isKeyDown(VK_LEFT) || input->isKeyDown(VK_RIGHT))
	{
		//this->animation = simon->getJumpingAnim();
		this->simon->setPosition(this->simon->getPosition().x + 6, this->simon->getPosition().y - 10);
		return;
	}

	// Set Data for sprite
	const SpriteData data = SpriteManager::getInstance()->getSpritesData()[IndexOfSpriteSheet::getInstance()->jump];
	this->simon->getSprite()->setSpriteDataRect(data.rect);
	this->simon->getSprite()->setSpriteWidth(data.width);
	this->simon->getSprite()->setSpriteHeigth(data.height);

	this->jumpFightAnim = simon->getFightingAnimation();
}

void SimonStateJumping::handleInput(float dt)
{
	if (input->isKeyDown(VK_LEFT) || input->isKeyDown(VK_RIGHT))
	{
		this->simon->updateHorizontal(dt);
	}

	if (this->simon->isFall() == false)
	{
		if (input->isKeyDown(VK_Z))
		{
			this->animation = jumpFightAnim;
			this->animation->start();
		}
		if (input->isKeyUp(VK_Z))
		{
			if (animation != nullptr)
				animation->stop();
		}
		if (input->isKeyDown(VK_X))
		{
			this->simon->setFall(false);
			this->simon->updateVertical(dt);
		}

		if (input->isKeyUp(VK_X))
		{
			this->simon->setFall(true);
		}
	}
	else
	{
		this->simon->updateVertical(dt);

		if (this->simon->getPosition().y >= GAME_HEIGHT * 0.8)
		{
			this->simon->setFall(false);
			this->simon->setStatus(eStatus::STANDING);
			SimonStateManager::getInstance()->changeStateTo(eStatus::STANDING);
		}
	}

	
}

void SimonStateJumping::update(float dt)
{
	//if (this->animation != nullptr)
	//	this->animation->update(dt);

	this->handleInput(dt);
}

void SimonStateJumping::onStart()
{
	//if (this->animation != nullptr)
	//	this->animation->start();
}

void SimonStateJumping::onExit()
{
	//if (this->animation != nullptr)
	//	this->animation->stop();
}