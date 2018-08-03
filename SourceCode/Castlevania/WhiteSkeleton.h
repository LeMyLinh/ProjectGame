#pragma once
#include "Animation.h"
#include "BaseObject.h"
#include "Camera.h"

class WhiteSkeleton : public BaseObject
{
private:
	Animation * whiteAnimation;

	VECTOR2 startPosition;
	VECTOR2 target;

	float timeDeath;

	//Đường cong Bezier
	float t;

public:
	WhiteSkeleton();
	WhiteSkeleton(TextureManager *texture, Graphics *graphics);
	~WhiteSkeleton();

	void update(float dt);
	void draw();
	void release();

	VECTOR2 getTarget();
	void setTarget(VECTOR2 target);

};

