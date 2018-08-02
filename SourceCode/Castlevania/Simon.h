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
#define MIN_JUMP 32
#define MAX_JUMP 80
#define SIMON_HEIGHT 32
#define MAX_WIDTH 16
#define MAX_HEIGHT 31
#define WIDTH_WALK 16
#define HEIGHT_WALK 31

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
	bool moveRight;
	bool moveLeft;
	bool jump;
	bool moveHorizontal;
	bool moveVertical;
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
	bool canMoveleft();
	bool canMoveRight();
	bool isJump();

	void setFall(bool isFall);
	void setCanMoveRight(bool moveRight);
	void setCanMoveLeft(bool moveLeft);
	void setJump(bool jump);

	//Animation* getStartingAnim();
	Animation* getWalkingAnimation();
	Animation* getFightingAnimation();
	Animation* getUpStairAnimation();
	Animation* getDownStairAnimation();
	Animation* getUpFightAnimation();
	Animation* getDownFightAnimation();
	Animation* getSitFightAnimation();

	void setCamera(Camera* cam);

	void onCollision(BaseObject *object, float dt);
};