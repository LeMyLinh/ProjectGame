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
}

void SimonStateJumping::setBoundCollision()
{
	Rect rect;

	if (this->simon->getDirection() == eDirection::right)
	{
		VECTOR2 position(this->simon->getPosition().x, simon->getPosition().y + HEIGHT_WALK);
		rect.left = position.x + 1;
		rect.right = position.x + (MAX_WIDTH) - 1;
		rect.top = position.y - (MAX_HEIGHT) + 1;
		rect.bottom = position.y - 1;
	}
	else
	{
		VECTOR2 position(this->simon->getPosition().x, simon->getPosition().y + HEIGHT_WALK);
		rect.left = position.x - MAX_WIDTH + 1;
		rect.right = position.x - 1;
		rect.top = position.y - (MAX_HEIGHT)+1;
		rect.bottom = position.y - 1;
	}
	this->simon->setBoundCollision(rect);
}

void SimonStateJumping::init()
{
	this->simon->getSprite()->setDataSprite(IndexOfSpriteSheet::getInstance()->jump);

	if (input->isKeyDown(VK_LEFT) || input->isKeyDown(VK_RIGHT))
	{
		//this->simon->setPosition(this->simon->getPosition().x, this->simon->getPosition().y - 15);
		this->simon->setOrigin(VECTOR2(0.5f, 0.5f));
		return;
	}

	if (simon->getDirection() == eDirection::left)
	{
		this->simon->setOrigin(VECTOR2(1.0f, 0));
	}
	else
	{
		this->simon->setOrigin(VECTOR2(0, 0));
	}
}

void SimonStateJumping::handleInput(float dt)
{
#pragma region Horizontal
	if (input->isKeyDown(VK_RIGHT) && input->isKeyUp(VK_LEFT))
	{
		//// Handle horizontal
		//this->simon->updateHorizontal(dt);
		this->simon->setVelocityX(SIMON_VERLOCITY_X);

		// Handle direction
		if (this->simon->isInDirection(eDirection::left))
		{
			//this->simon->setScaleX(1);
			this->simon->setFlipX(false);

			Rect bound = simon->getBoundCollision();

			this->simon->setPositionX(bound.left -1);
			this->simon->setOrigin(VECTOR2(0, 0));
			this->simon->setDirection(eDirection::right);
		}
	}

	if (input->isKeyDown(VK_LEFT) && input->isKeyUp(VK_RIGHT))
	{
		//// Handle horizontal
		//this->simon->updateHorizontal(dt);
		this->simon->setVelocityX(- SIMON_VERLOCITY_X);

		// Handle direction
		if (this->simon->isInDirection(eDirection::right))
		{
			//this->simon->setScaleX(-1);
			this->simon->setFlipX(true);

			Rect bound = simon->getBoundCollision();

			//this->simon->setPositionX(this->simon->getPosition().x + this->simon->getSprite()->getWidth());
			this->simon->setPositionX(bound.right + 1);
			this->simon->setOrigin(VECTOR2(1.0f, 0));

			this->simon->setDirection(eDirection::left);
		}
	}

	//if (input->isKeyDown(VK_LEFT) || input->isKeyDown(VK_RIGHT))
	//{
	//	this->simon->updateHorizontal(dt);
	//}


#pragma endregion

#pragma region Vertical
	
	this->simon->setVelocityY(-SIMON_VERLOCITY_Y);

	if (input->isKeyUp(VK_X) && jumpDistance >= MIN_JUMP)
	{
		this->simon->setFall(true);
	}

	if (this->simon->isFall() == false)
	{
		/*if (input->isKeyDown(VK_X))
		{
			this->simon->setFall(false);
			this->simon->updateVertical(dt);
		}*/
		float distance = simon->getVelocity().y*dt;
		jumpDistance += distance * -1.0f;

		if (jumpDistance <= MAX_JUMP)
		{
			this->simon->setVelocityY(-SIMON_VERLOCITY_Y);
			this->simon->setFall(false);
		}
		else
		{
			jumpDistance = 0;
			this->simon->setFall(true);
			this->simon->setVelocityY(SIMON_VERLOCITY_Y);
		}
	}
	else
	{
		this->simon->setVelocityY(SIMON_VERLOCITY_Y);
	}


	/*}
	else
	{
		this->simon->updateVertical(dt);

		if (this->simon->getPosition().y >= GAME_HEIGHT * 0.8)
		{
			this->simon->setFall(false);
			this->simon->setStatus(eStatus::STANDING);
			SimonStateManager::getInstance()->changeStateTo(eStatus::STANDING);
		}
	}*/
#pragma endregion
	
}

void SimonStateJumping::onCollision(BaseObject * obj, float dt)
{
	CollideDirection collideDirection;
	Rect collideRect;
	float addX = 0, addY = 0;
	if (Collision::getInstance()->checkCollision(simon, obj, dt, collideDirection, collideRect))
	{
		switch (obj->getId())
		{
			//handle collision with wall
		case eID::WALL:
			switch (collideDirection)
			{
			case CollideDirection::LEFT:

				this->simon->setCanMoveRight(false);
				this->simon->setVelocityX(0);
				break;
			case CollideDirection::RIGHT:
				this->simon->setCanMoveLeft(false);
				this->simon->setVelocityX(0);
				break;
			case CollideDirection::TOP:
				jumpDistance = 0;
				//set jump = false, when user release jump button set to true
				this->simon->setJump(false);
				//when player release jump button jump is set true
				this->simon->setJump(false);
				//set fall to false
				this->simon->setFall(false);
				//reset velocity
				this->simon->setVelocity(VECTOR2(0, 0));
				addY = collideRect.top;
				if (animation == NULL)
				{
					addX = this->simon->getPosition().x;
				}
				else
				{
					if (this->simon->isInDirection(eDirection::right))
					{
						addX = this->simon->getPosition().x - WIDTH_WALK * 0.5f;
					}
					else
					{
						addX = this->simon->getPosition().x + WIDTH_WALK * 0.5f;
					}

				}
				this->simon->setPosition(VECTOR2(addX, addY));
				this->simon->setStatus(eStatus::STANDING);
				SimonStateManager::getInstance()->changeStateTo(eStatus::STANDING);
				break;
			case CollideDirection::BOTTOM:
				jumpDistance = 0;
				this->simon->setFall(true);
				this->simon->setVelocityY(0);
				addY = collideRect.bottom;
				this->simon->setVelocityY(0);

				if (animation != NULL)
				{
					addY = addY + HEIGHT_WALK * 0.5f;
				}
				this->simon->setPositionY(addY);
				break;
			}
			break;
			//another object
		default:
			break;
		}

	}
}

void SimonStateJumping::update(float dt)
{
	//if (this->animation != nullptr)
	//	this->animation->update(dt);

	if (this->simon->canMoveleft() || this->simon->canMoveRight())
	{
		this->simon->updateHorizontal(dt);
	}

	this->simon->updateVertical(dt);

	setBoundCollision();

	this->simon->setCanMoveLeft(true);
	this->simon->setCanMoveRight(true);
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