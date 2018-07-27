#include "SimonStateStand.h"
#include "SimonStateManager.h"


SimonStateStand::SimonStateStand()
{

}

SimonStateStand::SimonStateStand(Simon* simon, Input* input) : BaseState(simon, input)
{
	isPressed = false;
}

SimonStateStand::~SimonStateStand()
{
}

void SimonStateStand::init()
{
	const SpriteData data = SpriteManager::getInstance()->getSpritesData()[IndexOfSpriteSheet::getInstance()->stand];
	this->simon->getSprite()->setSpriteDataRect(data.rect);
	this->simon->getSprite()->setSpriteWidth(data.width);
	this->simon->getSprite()->setSpriteHeigth(data.height);

	if (this->simon->isInDirection(eDirection::left))
	{
		const SpriteData data = SpriteManager::getInstance()->getSpritesData()[IndexOfSpriteSheet::getInstance()->stand];
		this->simon->getSprite()->setSpriteDataRect(data.rect);
		this->simon->getSprite()->setSpriteWidth(data.width);
		this->simon->getSprite()->setSpriteHeigth(data.height);
		this->simon->getSprite()->flipHorizontal(true);
	}
}

void SimonStateStand::handleInput(float dt)
{
	if (input->isKeyDown(VK_RIGHT) || input->isKeyDown(VK_LEFT))
	{
		this->simon->setStatus(eStatus::WALKING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::WALKING);
		//simon->walking(dt);
	}

	if (input->isKeyDown(VK_UP))
	{
		//Xử lý nếu gần cầu thang
	}

	if (input->isKeyDown(VK_X))
	{
		this->simon->setStatus(eStatus::JUMPING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::JUMPING);
	}

	if (input->isKeyDown(VK_DOWN))
	{
		this->simon->setStatus(eStatus::SITTING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::SITTING);
		//Xử lý nếu gần cầu thang
	}

	if (input->isKeyDown(VK_Z))
	{
		this->animation = simon->getFightingAnimation();
		animation->start();
	}

	if (input->isKeyUp(VK_Z) && this->animation == simon->getFightingAnimation())
	{		
		animation->stop();
	}
}

void SimonStateStand::update(float dt)
{
		handleInput(dt);
}

void SimonStateStand::onStart()
{
}

void SimonStateStand::onExit()
{
}