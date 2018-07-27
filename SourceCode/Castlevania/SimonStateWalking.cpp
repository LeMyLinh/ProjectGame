#include "SimonStateWalking.h"
#include "SimonStateManager.h"


SimonStateWalking::SimonStateWalking()
{
}

SimonStateWalking::SimonStateWalking(Simon *simon, Input *input) : BaseState(simon, input)
{
}

SimonStateWalking::~SimonStateWalking()
{
	walking = nullptr;
	walkFighting = nullptr;

	delete walking, walkFighting;
}

void SimonStateWalking::init()
{
	walking = simon->getWalkingAnimation();
	walkFighting = simon->getFightingAnimation();
	this->animation = simon->getWalkingAnimation();
}

void SimonStateWalking::handleInput(float dt)
{
	if (input->isKeyDown(VK_RIGHT) && input->isKeyUp(VK_LEFT))
	{
		// Handle horizontal
		this->simon->updateHorizontal(dt);

		// Handle direction
		if (this->simon->isInDirection(eDirection::left))
		{
			this->simon->setScaleX(1);
			this->simon->setPositionX(this->simon->getPosition().x /*- this->simon->getSprite()->getWidth()*/);
			this->simon->setDirection(eDirection::right);
		}
	}

	if (input->isKeyDown(VK_LEFT) && input->isKeyUp(VK_RIGHT))
	{
		// Handle horizontal
		this->simon->updateHorizontal(dt);

		// Handle direction
		if (this->simon->isInDirection(eDirection::right))
		{
			this->simon->setScaleX(-1);
			this->simon->setPositionX(this->simon->getPosition().x /*+ this->simon->getSprite()->getWidth()*/);
			this->simon->setDirection(eDirection::left);
		}
	}

	// Handle horizontal
	if (input->isKeyDown(VK_LEFT) && input->isKeyDown(VK_RIGHT))
	{
		this->simon->updateHorizontal(dt);
	}

	if (input->isKeyDown(VK_Z))
	{
		this->animation->stop();

		this->animation = walkFighting;
		this->animation->start();
	}	

	if (input->isKeyUp(VK_UP) && input->isKeyUp(VK_Z) && (input->isKeyDown(VK_LEFT) || input->isKeyDown(VK_RIGHT)))
	{
		this->animation->stop();

		this->animation = walking;
		this->animation->start();
	}

	if (input->isKeyUp(VK_RIGHT) && input->isKeyUp(VK_LEFT))
	{
		this->simon->setStatus(eStatus::STANDING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::STANDING);
	}

	if (input->isKeyDown(VK_X))
	{
		this->animation->stop();

		this->simon->setStatus(eStatus::JUMPING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::JUMPING);
	}
}

void SimonStateWalking::update(float dt)
{
	this->animation->update(dt);
	handleInput(dt);
	simon->updateHorizontal(dt);
}

void SimonStateWalking::onStart()
{
	this->animation->start();
}

void SimonStateWalking::onExit()
{
	this->animation->stop();
}

