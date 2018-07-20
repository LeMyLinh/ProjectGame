#pragma once
#include "Sprite.h"
#include "Graphics.h"
#include "Input.h"
#include "SpriteManager.h"
#include "TextureManager.h"
#include "GameError.h"
#include "Animation.h"
#include "BaseObject.h"



class Simon : public BaseObject
{
private:
	Input * input;
	Animation	*currentAnimation,
		*walkingAnimation,
		*fightingAnimation;



public:
	Simon(TextureManager* textureM, Graphics* graphics, Input* input);
	Simon();
	~Simon();

	void setRect();
	void draw();
	void update(float dt);
	void release();
};