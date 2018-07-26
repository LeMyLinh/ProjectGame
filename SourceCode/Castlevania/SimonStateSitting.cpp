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

	this->simon->getSprite()->setSpriteDataRect(SpriteManager::getInstance()->getSpritesData()[IndexOfSpriteSheet::getInstance()->sit].rect);
}

void SimonStateSitting::handleInput(float dt)
{
	if (input->isKeyDown(VK_RIGHT) || input->isKeyDown(VK_LEFT))
	{
		this->simon->setStatus(eStatus::SITTING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::SITTING);

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
		this->simon->setStatus(eStatus::FIGHTING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::FIGHTING);

		animation = sitFightingAnim;
		animation->start();
	}

	if (input->isKeyUp(VK_Z))
	{
		if (animation == sitFightingAnim)
		{
			animation->stop();
		}
	}

}

void SimonStateSitting::update(float dt)
{
	//this->animation->update(dt);
	handleInput(dt);
}

void SimonStateSitting::onStart()
{
	
}

void SimonStateSitting::onExit()
{
	//this->animation->stop();
}