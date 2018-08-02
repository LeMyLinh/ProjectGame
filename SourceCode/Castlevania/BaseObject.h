#pragma once
#include "Sprite.h"
#include "IndexOfSpriteSheet.h"

class BaseObject
{
protected:
	Sprite * sprite;
	eID id;
	eStatus status;
	eDirection direction;

	Rect  boundCollision;
	VECTOR2 velocity;

public:
	BaseObject(eID id);
	BaseObject();
	~BaseObject();

	//virtual void handleInput(float dt) = 0;
	virtual void update(float dt);
	virtual void draw();

	eID getId();
	eStatus getStatus();
	virtual void setStatus(eStatus status);
	virtual bool isInStatus(eStatus status);

	eDirection getDirection();
	virtual void setDirection(eDirection direct);
	virtual bool isInDirection(eDirection direct);

	virtual VECTOR2 getPosition();
	//virtual float getPositionX();
	//virtual float getPositionY();

	virtual void setPosition(VECTOR2 position);
	virtual void setPosition(float x, float y);
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);

	virtual VECTOR2 getScale();
	virtual void setScale(VECTOR2 scale);
	virtual void setScaleX(float scaleX);
	virtual void setScaleY(float scaleY);

	virtual VECTOR2 getOrigin();
	virtual void setOrigin(VECTOR2 origin);

	virtual float getRotate();
	virtual void setRotate(float rotate);

	Sprite* getSprite();

	//TO DO: update position, velocity... if this object collide with another object(call before update() )
	virtual void onCollision(BaseObject* object, float dt);

	virtual void setBoundCollision(Rect rect);
	virtual Rect getBoundCollision();

	virtual void setFlipX(bool flipX) { sprite->setFlipX(flipX); }
	virtual void setFlipY(bool flipY) { sprite->setFlipY(flipY); }
	virtual VECTOR2 getVelocity();
	virtual void setVelocityX(float x);
	virtual void setVelocityY(float y);
	virtual void setVelocity(VECTOR2 velocity);	
};