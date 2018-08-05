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
 
void SimonStateWalking::setBoundCollision()
{
	Rect rect;

	if (this->simon->getDirection() == eDirection::right)
	{
		VECTOR2 position(this->simon->getPosition().x - WIDTH_WALK * 0.5f, simon->getPosition().y);
		rect.left = position.x + 1;
		rect.right = position.x + (MAX_WIDTH) - 1;
		rect.top = position.y - (MAX_HEIGHT) + 1;
		rect.bottom = position.y - 1;
	}
	else
	{
		VECTOR2 position(this->simon->getPosition().x + WIDTH_WALK * 0.5f, simon->getPosition().y);
		rect.left = position.x - MAX_WIDTH + 1;
		rect.right = position.x - 1;
		rect.top = position.y - (MAX_HEIGHT)+1;
		rect.bottom = position.y - 1;
	}
	this->simon->setBoundCollision(rect);
}

void SimonStateWalking::init()
{
	walking = simon->getWalkingAnimation();
	walkFighting = simon->getFightingAnimation();
	
	this->simon->setOrigin(VECTOR2(0.5f, 1));

	this->animation = walking;
}

void SimonStateWalking::handleInput(float dt)
{
#pragma region Horizontal
	if (input->isKeyDown(VK_LEFT) && input->isKeyUp(VK_RIGHT))
	{
		//// Handle horizontal
		//this->simon->updateHorizontal(dt);

		// Handle direction
		if (this->simon->isInDirection(eDirection::right))
		{
			//this->simon->setScaleX(-1);
			this->simon->setFlipX(true);
			//this->simon->setPositionX(this->simon->getPosition().x /*+ this->simon->getSprite()->getWidth()*/);
			this->simon->setDirection(eDirection::left);
		}

		this->simon->setVelocityX(-SIMON_VERLOCITY_X);
	}

	if (input->isKeyDown(VK_RIGHT) && input->isKeyUp(VK_LEFT))
	{
		//// Handle horizontal
		//this->simon->updateHorizontal(dt);

		// Handle direction
		if (this->simon->isInDirection(eDirection::left))
		{
			//this->simon->setScaleX(1);
			this->simon->setFlipX(false);
			//this->simon->setPositionX(this->simon->getPosition().x /*- this->simon->getSprite()->getWidth()*/);
			this->simon->setDirection(eDirection::right);
		}


		
		this->simon->setVelocityX(SIMON_VERLOCITY_X);
	}

	if ((input->isKeyUp(VK_RIGHT) && input->isKeyUp(VK_LEFT)) || (input->isKeyDown(VK_LEFT) && input->isKeyDown(VK_RIGHT)))
	{
		this->simon->setVelocityX(0);

		if (simon->getDirection() == eDirection::right)
			this->simon->setPositionX(this->simon->getPosition().x - WIDTH_WALK * 0.5f);
		else
			this->simon->setPositionX(this->simon->getPosition().x + WIDTH_WALK * 0.5f);

		this->simon->setStatus(eStatus::STANDING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::STANDING);
		return;
	}
#pragma endregion

	//// Handle horizontal
	//if (input->isKeyDown(VK_LEFT) && input->isKeyDown(VK_RIGHT))
	//{
	//	this->simon->updateHorizontal(dt);
	//}
	if (input->isKeyUp(VK_X) == true)
		this->simon->setJump(true);

	if (input->isKeyDown(VK_X) && this->simon->isJump() == true)
	{
		this->animation->stop();

		this->simon->setVelocityX(0);

		//if (simon->getDirection() == eDirection::right)
		//	this->simon->setPosition(VECTOR2(this->simon->getPosition().x + WIDTH_WALK * 0.5f, this->simon->getPosition().y - HEIGHT_WALK * 0.5f));
		//else
		//	this->simon->setPosition(VECTOR2(this->simon->getPosition().x - WIDTH_WALK * 0.5f, this->simon->getPosition().y - HEIGHT_WALK * 0.5f));
		this->simon->setPosition(VECTOR2(this->simon->getPosition().x, this->simon->getPosition().y - HEIGHT_WALK * 0.5f));

		this->simon->setStatus(eStatus::JUMPING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::JUMPING);
		return;
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
}

void SimonStateWalking::update(float dt)
{
	this->animation->update(dt);
	//handleInput(dt);
	simon->updateHorizontal(dt);

	setBoundCollision();

	this->simon->setVelocity(VECTOR2(0, 0));

	this->simon->setCanMoveLeft(true);

	this->simon->setCanMoveRight(true);
}

void SimonStateWalking::onStart()
{
	this->animation->start();
}

void SimonStateWalking::onExit()
{
	this->animation->stop();
}

void SimonStateWalking::onCollision(BaseObject *obj, float dt)
{
	CollideDirection collideDirection;
	Rect collideRect;

	if (!Collision::getInstance()->checkOnGround(simon->getBoundCollision(), dt*simon->getVelocity().x))
	{
		this->simon->setFall(true);
		this->simon->setVelocityX(0);
		//change orgin.y = 1 in running state to orgin.y = 0 in jumping state, so we change position.y		
		this->simon->setPositionY(this->simon->getPosition().y - HEIGHT_WALK);

		this->simon->setStatus(eStatus::JUMPING);
		SimonStateManager::getInstance()->changeStateTo(eStatus::JUMPING);

		return;
	}
	if (Collision::getInstance()->checkCollision(simon, obj, dt, collideDirection, collideRect))
	{
		switch (obj->getId())
		{
		case eID::WALL:
			switch (collideDirection)
			{
			case CollideDirection::LEFT:
				this->simon->setVelocityX(0);
				//not allow move left
				this->simon->setCanMoveRight(false);
				//change to standing state
				this->simon->setPositionX(this->simon->getPosition().x - WIDTH_WALK * 0.5f);
				this->simon->setStatus(eStatus::STANDING);
				SimonStateManager::getInstance()->changeStateTo(eStatus::STANDING);
				break;
			case CollideDirection::RIGHT:
				this->simon->setVelocityX(0);
				//not allow move right
				this->simon->setCanMoveLeft(false);
				//change to standing state
				this->simon->setPositionX(this->simon->getPosition().x + WIDTH_WALK * 0.5f);
				this->simon->setStatus(eStatus::STANDING);
				SimonStateManager::getInstance()->changeStateTo(eStatus::STANDING);
				break;
			case CollideDirection::TOP:
				break;
			}
			break;
		default:
			break;
		}

	}
}