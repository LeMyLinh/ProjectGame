#include "BaseState.h"



BaseState::BaseState()
{
	this->simon = nullptr;
}

BaseState::BaseState(Simon * simon, Input* input)
{
	this->simon = simon;
	this->input = input;
}


BaseState::~BaseState()
{
	this->simon = nullptr;
	delete this->simon;

	this->input = nullptr;
	delete this->input;

	this->animation = nullptr;
	delete this->animation;
}

void BaseState::setBoundCollision()
{
}

void BaseState::onCollision(BaseObject * obj, float dt)
{
}

void BaseState::onCollisionBullet(BaseObject * obj, float dt)
{
}