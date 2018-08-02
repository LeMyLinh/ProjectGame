#pragma once
#include "BaseState.h"
#include "Collision.h"

class SimonStateWalking :	public BaseState
{
private:
	Animation * walking,
		*walkFighting;
public:
	SimonStateWalking();
	SimonStateWalking(Simon *simon, Input *input);
	~SimonStateWalking();

	void init();
	void handleInput(float dt);
	void update(float dt);

	void setBoundCollision();
	void onCollision(BaseObject* obj, float dt);

	void onStart();
	void onExit();


};

