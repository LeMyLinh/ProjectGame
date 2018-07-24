#pragma once
#include "SimonStateStand.h"

class SimonStateManager
{
private:
	static SimonStateManager* instance;

	SimonStateStand* stateStart;
	BaseState* currentState;
public:
	static SimonStateManager* getInstance();
	void init(Simon* simon, Input* input);
	BaseState* getCurrentState();
	void changeStateTo(eStatus estatus);
	SimonStateManager();
	~SimonStateManager();
};

