#include "SimonStateSitting.h"
#include "SimonStateManager.h"


SimonStateSitting::SimonStateSitting()
{
}

SimonStateSitting::SimonStateSitting(Simon *simon, Input *input):BaseState(simon, input)
{
}

SimonStateSitting::~SimonStateSitting()
{
}

void SimonStateSitting::init()
{
	sitFightingAnim = simon->getSitFightAnimation();
	
	this->simon->getSprite()->setDataSprite(IndexOfSpriteSheet::getInstance()->sit);

	this->simon->setPosition(this->simon->getPosition().x, this->simon->getPosition().y - 15);
}

void SimonStateSitting::handleInput(float dt)
{
	if (input->isKeyDown(VK_RIGHT) && input->isKeyUp(VK_LEFT))
	{
		// Handle direction
		if (this->simon->isInDirection(eDirection::left))
		{
			this->simon->setScaleX(1);
			//this->simon->setPositionX(this->simon->getPosition().x - this->simon->getSprite()->getWidth());
			this->simon->setDirection(eDirection::right);
		}

		// Handle horizontal
		this->simon->updateHorizontal(dt);
	}

	if (input->isKeyDown(VK_LEFT) && input->isKeyUp(VK_RIGHT))
	{	
		// Handle direction
		if (this->simon->isInDirection(eDirection::right))
		{
			this->simon->setScaleX(-1);
			//this->simon->setPositionX(this->simon->getPosition().x + this->simon->getSprite()->getWidth());
			this->simon->setDirection(eDirection::left);
		}
		// Handle horizontal
		this->simon->updateHorizontal(dt);
	}

	if (input->isKeyDown(VK_UP))
	{
		this->simon->setStatus(eStatus::STANDING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::STANDING);
	}

	if (input->isKeyDown(VK_X))
	{
		this->simon->setStatus(eStatus::STANDING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::STANDING);
	}

	if (input->isKeyDown(VK_Z))
	{
		//fight
	}

	//if (input->isKeyUp(VK_Z))
	//{
	//	if (animation == sitFightingAnim)
	//	{
	//		animation->stop();
	//	}
	//}

}

void SimonStateSitting::update(float dt)
{
	//this->animation->update(dt);
	//handleInput(dt);
}

void SimonStateSitting::onStart()
{
	
}

void SimonStateSitting::onExit()
{
	//this->animation->stop();
}