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

#define SIMON_VERLOCITY_X 20
#define SIMON_VERLOCITY_Y 20
#define MAX_JUMP_HEIGHT 80

class Simon : public BaseObject
{
private:
	Input * input;
	Animation		*walkingAnimation,
		*fightingAnimation,
		*upStairAnimation,
		*downStairAnimation,
		*up_fight_animation,
		*down_fight_animation,
		*sit_fight_animation;

	bool isFalling;
	float totalJumpHeight;
	Camera* camera;

public:
	Simon(TextureManager* textureM, Graphics* graphics, Input* input);
	Simon();
	~Simon();

	void draw();
	void handleInput(float dt);
	void update(float dt);
	void release();

	//void updateDirection();
	void updateHorizontal(float dt);
	void updateVertical(float dt);
	
	bool isFall();
	void setFall(bool isFall);

	//Animation* getStartingAnim();
	Animation* getWalkingAnimation();
	Animation* getFightingAnimation();
	Animation* getUpStairAnimation();
	Animation* getDownStairAnimation();
	Animation* getUpFightAnimation();
	Animation* getDownFightAnimation();
	Animation* getSitFightAnimation();

	void setCamera(Camera* cam);
};