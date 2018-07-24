#pragma once
#include "Sprite.h"
#include "Graphics.h"
#include "Input.h"
#include "SpriteManager.h"
#include "TextureManager.h"
#include "GameError.h"
#include "Animation.h"
#include "BaseObject.h"
#include "Camera.h"

#define SIMON_VERLOCITY 100

class Simon : public BaseObject
{
private:
	Input * input;
	Animation	//*currentAnimation,
		//*standingAnimation,
		*walkingAnimation,
		*fightingAnimation,
		//*jumpingAnimation,
		//*sittingAnimation,
		*sit_fight_animation;

	Camera* camera;

public:
	Simon(TextureManager* textureM, Graphics* graphics, Input* input);
	Simon();
	~Simon();

	void setRect();
	void draw();
	void handleInput(float dt);
	void update(float dt);
	void release();

	void updateDirection();
	void running(float dt);
	void turnUp();
	void jump();
	
	Animation * getStartingAnim();
	void setCamera(Camera* cam);
};