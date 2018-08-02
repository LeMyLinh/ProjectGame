#include "SimonStateStand.h"
#include "SimonStateManager.h"

#define TIME_TO_WALK 0.1f

SimonStateStand::SimonStateStand()
{

}

SimonStateStand::SimonStateStand(Simon* simon, Input* input) : BaseState(simon, input)
{
	simon->setOrigin(VECTOR2(0, 1.0f));
	init();
}

SimonStateStand::~SimonStateStand()
{
}

void SimonStateStand::setBoundCollision()
{
	Rect rect;

	if (this->simon->getDirection() == eDirection::right)
	{
		//VECTOR2 position(this->simon->getPosition().x, simon->getPosition().y);
		rect.left = simon->getPosition().x + 1;
		rect.right = simon->getPosition().x + (MAX_WIDTH)-1;
		rect.top = simon->getPosition().y - (MAX_HEIGHT)+1;
		rect.bottom = simon->getPosition().y - 1;		
	}
	else
	{
		rect.left = simon->getPosition().x  - MAX_WIDTH +1;
		rect.right = simon->getPosition().x -1;
		rect.top = simon->getPosition().y - (MAX_HEIGHT) +1;
		rect.bottom = simon->getPosition().y - 1;
	}
	this->simon->setBoundCollision(rect);
}

void SimonStateStand::init()
{
	this->simon->getSprite()->setDataSprite(IndexOfSpriteSheet::getInstance()->stand);

	if (simon->getDirection() == eDirection::left)
	{
		this->simon->setOrigin(VECTOR2(1.0f, 1.0f));
	}
	else
	{
		this->simon->setOrigin(VECTOR2(0, 1.0f));
	}

	timeToWalk = 0;
	/*if (this->simon->isInDirection(eDirection::left))
	{
		const SpriteData *data = &(SpriteManager::getInstance()->getSpritesData()[IndexOfSpriteSheet::getInstance()->stand]);
		this->simon->getSprite()->setSpriteDataRect(data->rect);
		this->simon->getSprite()->setSpriteWidth(data->width);
		this->simon->getSprite()->setSpriteHeigth(data->height);
		this->simon->setOrigin(VECTOR2(0, 1.0f));

		this->simon->getSprite()->flipHorizontal(true);
	}*/
}

void SimonStateStand::handleInput(float dt)
{
	setBoundCollision();

	if (input->isKeyUp(VK_LEFT) && input->isKeyUp(VK_RIGHT))
		timeToWalk = 0;
	
	if (input->isKeyDown(VK_LEFT) && input->isKeyUp(VK_RIGHT))
	{
		if (this->simon->isInDirection(eDirection::right))
		{
			Rect bound = simon->getBoundCollision();

			this->simon->setPositionX(bound.right + 1);

			this->simon->setOrigin(VECTOR2(1.0f, 1.0f));
			
			this->simon->setFlipX(true);

			this->simon->setDirection(eDirection::left);
		}

		if (this->simon->canMoveleft() == true)
		{
			timeToWalk += dt;

			if (timeToWalk > TIME_TO_WALK)
			{
				this->simon->setPositionX(this->simon->getPosition().x - WIDTH_WALK * 0.5f);

				this->simon->setDirection(eDirection::left);

				this->simon->setStatus(eStatus::WALKING);

				SimonStateManager::getInstance()->changeStateTo(eStatus::WALKING);

				this->simon->setJump(false);

				timeToWalk = 0;

				return;
			}
		}
	}

	if (input->isKeyDown(VK_RIGHT) && input->isKeyUp(VK_LEFT))
	{
		if (this->simon->isInDirection(eDirection::left))
		{
			Rect bound = simon->getBoundCollision();

			this->simon->setPositionX(bound.left - 1);

			this->simon->setOrigin(VECTOR2(0, 1.0f));

			this->simon->setFlipX(false);

			this->simon->setDirection(eDirection::right);
		}

		if (this->simon->canMoveRight() == true)
		{
			timeToWalk += dt;

			if (timeToWalk > TIME_TO_WALK)
			{
				this->simon->setPositionX(this->simon->getPosition().x + WIDTH_WALK * 0.5f);

				this->simon->setDirection(eDirection::right);

				this->simon->setStatus(eStatus::WALKING);

				SimonStateManager::getInstance()->changeStateTo(eStatus::WALKING);

				this->simon->setJump(false);

				timeToWalk = 0;

				return;
			}
		}
	}

	if (input->isKeyUp(VK_X))
	{
		this->simon->setJump(true);
	}

	if (input->isKeyDown(VK_X) && this->simon->isJump() == true)
	{
		this->simon->setFall(false);
		this->simon->setVelocityX(0);
		this->simon->setPositionY(this->simon->getPosition().y - HEIGHT_WALK);

		this->simon->setStatus(eStatus::JUMPING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::JUMPING);
		return;
	}

	//if (input->isKeyDown(VK_RIGHT) || input->isKeyDown(VK_LEFT))
	//{
	//	this->simon->setStatus(eStatus::WALKING);
	//	SimonStateManager::getInstance()->changeStateTo(eStatus::WALKING);
	//}

	if (input->isKeyDown(VK_UP))
	{
		//Xử lý nếu gần cầu thang
	}

	if (input->isKeyDown(VK_DOWN))
	{
		this->simon->setStatus(eStatus::SITTING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::SITTING);
		//Xử lý nếu gần cầu thang
	}

	if (input->isKeyDown(VK_Z))
	{
		/*this->animation = simon->getFightingAnimation();
		animation->start();*/
	}

	//if (input->isKeyUp(VK_Z) && this->animation == simon->getFightingAnimation())
	//{		
	//	animation->stop();
	//}
}

void SimonStateStand::update(float dt)
{
	//this->handleInput(dt);
}

void SimonStateStand::onStart()
{
}

void SimonStateStand::onExit()
{
}