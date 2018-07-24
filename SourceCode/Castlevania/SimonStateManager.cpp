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
	stateStart = new SimonStateStand();
	currentState = stateStart;
}


SimonStateManager::~SimonStateManager()
{
	delete stateStart;
	delete currentState;
}

void SimonStateManager::init(Simon * simon, Input * input)
{
	stateStart = new SimonStateStand(simon, input);
	currentState = stateStart;
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
	case eStatus::NORMAL:
	{
		currentState = stateStart;
	}
	default:
		break;
	}


	currentState->init();
	currentState->onStart();
}