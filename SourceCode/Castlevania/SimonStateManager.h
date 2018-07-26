#pragma once
#include "SimonStateStand.h"
#include "SimonStateWalking.h"
#include "SimonStateSitting.h"
#include "SimonStateJumping.h"


class SimonStateManager
{
private:
	static SimonStateManager* instance;

	SimonStateStand *stateStand;
	SimonStateWalking *stateWalking;
	SimonStateSitting *stateSitting;
	SimonStateJumping *stateJumping;


	BaseState* currentState;
public:
	static SimonStateManager* getInstance();
	void init(Simon* simon, Input* input);
	BaseState* getCurrentState();
	void changeStateTo(eStatus estatus);
	SimonStateManager();
	~SimonStateManager();
};

