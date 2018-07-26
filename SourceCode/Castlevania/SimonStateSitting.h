#pragma once
#include "BaseState.h"
class SimonStateSitting :	public BaseState
{
private:
	Animation * sitFightingAnim;
public:
	SimonStateSitting();
	SimonStateSitting(Simon *simon, Input *input);
	~SimonStateSitting();

	void init();
	void handleInput(float dt);
	void update(float dt);

	void onStart();
	void onExit();
};

