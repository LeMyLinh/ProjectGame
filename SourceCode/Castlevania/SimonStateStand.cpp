#include "SimonStateStand.h"
#include "SimonStateManager.h"


SimonStateStand::SimonStateStand()
{

}

SimonStateStand::SimonStateStand(Simon* simon, Input* input) : BaseState(simon, input)
{
	animation = simon->getStartingAnim();
	animation->start();
}

SimonStateStand::~SimonStateStand()
{
}

void SimonStateStand::init()
{
}

void SimonStateStand::handleInput(float dt)
{
	if (input->isKeyDown(VK_RIGHT) || input->isKeyDown(VK_LEFT))
	{
		SimonStateManager::getInstance()->changeStateTo(eStatus::WALKING);
		simon->running(dt);
	}

	if (input->isKeyDown(VK_UP))
	{
		SimonStateManager::getInstance()->changeStateTo(eStatus::NORMAL);
	}

	if (input->isKeyDown(VK_X))
	{
		SimonStateManager::getInstance()->changeStateTo(eStatus::JUMPING);
	}
}

void SimonStateStand::update(float dt)
{
	animation->update(dt);

	if (animation->isFinished())
	{
		handleInput(dt);
	}
}

void SimonStateStand::onStart()
{
}

void SimonStateStand::onExit()
{
}