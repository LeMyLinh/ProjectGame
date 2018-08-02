#pragma once
#include "BaseState.h"

class SimonStateStand : public BaseState
{
private:
	float timeToWalk;

public:
	SimonStateStand();
	SimonStateStand(Simon* simon, Input* input);
	~SimonStateStand();

	void init();
	void setBoundCollision();

	void handleInput(float dt);
	void update(float dt);

	void onStart();
	void onExit();
};

