#pragma once
#include "BaseState.h"

class SimonStateJumping : public BaseState
{
private:
	//Animation * jumpFightAnim;
	float jumpDistance;

public:
	SimonStateJumping();
	SimonStateJumping(Simon *simon, Input *input);
	~SimonStateJumping();

	void init();
	void handleInput(float dt);
	void update(float dt);

	void setBoundCollision();
	void onCollision(BaseObject *obj, float dt);

	void onStart();
	void onExit();
};

