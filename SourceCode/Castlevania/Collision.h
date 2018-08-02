#pragma once

#include "Define.h"
#include "BaseObject.h"
#include "ObjectManager.h"

class Collision
{
private:
	static Collision* instance;
	CollideDirection collideDirection;
public:
	static Collision * getInstance();
	//TO DO: true if object is on ground
	bool checkOnGround(Rect obj, float distance);
	//TO DO: true if one rectangle is colliding with another
	bool isCollide(Rect myRect, Rect otherRect);
	//TO DO: true if one object will collide with another
	bool checkCollision(BaseObject* myObj, BaseObject* otherObj, float frametime, CollideDirection& direction, Rect& collideRect);
	//TO DO: calculate collision rect
	Rect   CalculateCollisionRect(Rect   rect1, Rect   rect2);
	//TO DO: return collide area
	Rect   getSweptBroadphaseRect(BaseObject* entity, float frametime);
	Collision();
	~Collision();

	void release();
};

