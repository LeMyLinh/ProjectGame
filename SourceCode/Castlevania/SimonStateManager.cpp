#include "SimonStateManager.h"

SimonStateManager* SimonStateManager::instance = nullptr;

SimonStateManager * SimonStateManager::getInstance()
{
	if (instance == nullptr)
		instance = new SimonStateManager();

	return instance;
}

SimonStateManager::SimonStateManager()
{
	stateStand = new SimonStateStand();
	currentState = stateStand;
}


SimonStateManager::~SimonStateManager()
{
	stateStand = nullptr;
	stateWalking = nullptr;
	stateSitting = nullptr;
	stateJumping = nullptr;


	currentState = nullptr;

	delete stateStand;
	delete stateWalking;
	delete stateSitting;
	delete stateJumping;


	delete currentState;
}

void SimonStateManager::init(Simon * simon, Input * input)
{
	stateStand = new SimonStateStand(simon, input);
	stateWalking = new SimonStateWalking(simon, input);
	stateSitting = new SimonStateSitting(simon, input);
	stateJumping = new SimonStateJumping(simon, input);

	currentState = stateStand;
}

BaseState * SimonStateManager::getCurrentState()
{
	return this->currentState;
}

void SimonStateManager::changeStateTo(eStatus eStatus)
{
	if (currentState != nullptr)
		currentState->onExit();

	switch (eStatus)
	{
	case eStatus::STANDING:
	{
		currentState = stateStand;
		break;
	}
	case eStatus::WALKING:
	{
		currentState = stateWalking;
		break;
	}
	case eStatus::SITTING:
	{
		currentState = stateSitting;
		break;
	}
	case eStatus::JUMPING:
	{
		currentState = stateJumping;
		break;
	}
	default:
		break;
	}


	currentState->init();
	currentState->onStart();
}