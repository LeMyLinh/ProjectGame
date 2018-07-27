#pragma once
#include "BaseState.h"

class SimonStateJumping : public BaseState
{
private:
	//Animation * jumpFightAnim;
public:
	SimonStateJumping();
	SimonStateJumping(Simon *simon, Input *input);
	~SimonStateJumping();

	void init();
	void handleInput(float dt);
	void update(float dt);

	void onStart();
	void onExit();
};

